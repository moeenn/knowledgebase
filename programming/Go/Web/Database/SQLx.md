
```go
package main

import (
	"context"
	"database/sql"
	"fmt"
	"log/slog"
	"os"
	"time"

	"github.com/jmoiron/sqlx"
	_ "github.com/lib/pq"
)

// this interface is satisfied by both *sqlx.DB and *sqlx.Tx. It allows us to
// use both of them interchangeably.
type DBExec interface {
	NamedExecContext(ctx context.Context, query string, args any) (sql.Result, error)
	PrepareNamedContext(ctx context.Context, query string) (*sqlx.NamedStmt, error)
}

// sql column names must be in snake case. camel case with cause problems
// because all column names are converted to lower case when being sent to the db.
type Entity struct {
	Id        string       `db:"id"`
	Name      string       `db:"name"`
	CreatedAt time.Time    `db:"created_at"`
	DeletedAt sql.NullTime `db:"deleted_at"`
}

type EntityRepo struct {
	db     *sqlx.DB
	logger *slog.Logger
}

func NewEntityRepo(db *sqlx.DB, logger *slog.Logger) *EntityRepo {
	return &EntityRepo{
		logger: logger,
		db:     db,
	}
}

const createEntityQuery string = `
	insert into entity (id, name, created_at, deleted_at)
	values (:id, :name, :created_at, :deleted_at)
`

func (r *EntityRepo) CreateEntity(ctx context.Context, tx DBExec, entities []*Entity) error {
	var db DBExec = r.db
	if tx != nil {
		db = tx
	}

	// this method allows multiple inserts, but doesn't allow batch updates.
	_, err := db.NamedExecContext(ctx, createEntityQuery, entities)
	if err != nil {
		return fmt.Errorf("failed to save entities: %w", err)
	}

	return nil
}

const updateEntityQuery string = `
	update entity
	set name = :name,
		deleted_at = :deleted_at
	where id = :id
`

func (r *EntityRepo) UpdateEntities(ctx context.Context, tx DBExec, entities []*Entity) error {
	var db DBExec = r.db
	if tx != nil {
		db = tx
	}

	params := make([]any, len(entities))
	for i := range entities {
		params[i] = entities[i]
	}

	// prepare once, multiple executions are faster.
	stmt, err := db.PrepareNamedContext(ctx, updateEntityQuery)
	if err != nil {
		return fmt.Errorf("failed to prepare statement: %w", err)
	}
	defer stmt.Close()

	for _, entity := range entities {
		if _, err := stmt.ExecContext(ctx, entity); err != nil {
			return fmt.Errorf("failed to update record: %w", err)
		}
	}

	return nil
}

const listEntitiesQuery string = `
	select *, count(*) over() as total_count from entity
	where deleted_at is null
	limit :limit
	offset :offset
`

type LimitAndOffset struct {
	Limit  int `db:"limit"`
	Offset int `db:"offset"`
}

type ListEntitiesQueryResult struct {
	Entity
	TotalCount int `db:"total_count"`
}

func (r *EntityRepo) ListEntities(ctx context.Context, args *LimitAndOffset) ([]*Entity, int, error) {
	rows, err := r.db.NamedQueryContext(ctx, listEntitiesQuery, args)
	if err != nil {
		return nil, 0, fmt.Errorf("failed to query entities: %w", err)
	}

	defer rows.Close()
	entities := []*Entity{}
	totalCount := 0

	for rows.Next() {
		var result ListEntitiesQueryResult
		if err := rows.StructScan(&result); err != nil {
			return nil, 0, fmt.Errorf("failed to read entity record: %w", err)
		}
		totalCount = result.TotalCount
		entities = append(entities, &result.Entity)
	}

	return entities, totalCount, nil
}

func run() error {
	logger := slog.New(slog.NewJSONHandler(os.Stdout, nil))
	db, err := sqlx.Open("postgres", "postgresql://devuser:devpass@localhost:5432/dev?sslmode=disable")
	if err != nil {
		return fmt.Errorf("failed to open database connection: %w", err)
	}

	defer func() {
		if err := db.Close(); err != nil {
			logger.Error("failed to close db connection", "error", err.Error())
		}
	}()

	ctx := context.Background()
	if err := db.PingContext(ctx); err != nil {
		return fmt.Errorf("failed to ping database: %w", err)
	}

	entityRepo := NewEntityRepo(db, logger)
	dummyEntities := []*Entity{
		{
			Id:        "one",
			Name:      "One",
			CreatedAt: time.Now(),
			DeletedAt: sql.NullTime{},
		},
		{
			Id:        "two",
			Name:      "Two",
			CreatedAt: time.Now(),
			DeletedAt: sql.NullTime{},
		},
	}

	if err := entityRepo.CreateEntity(ctx, nil, dummyEntities); err != nil {
		return err
	}

	entities, totalCount, err := entityRepo.ListEntities(ctx, &LimitAndOffset{
		Limit:  10,
		Offset: 0,
	})

	if err != nil {
		return err
	}

	fmt.Printf("Total: %d\n", totalCount)
	for _, e := range entities {
		fmt.Printf("%+v\n", e)
	}

	updatedEntities := []*Entity{
		{
			Id:        "one",
			Name:      "One (Updated)",
			CreatedAt: time.Now(),
			DeletedAt: sql.NullTime{},
		},
		{
			Id:        "two",
			Name:      "Two (Updated)",
			CreatedAt: time.Now(),
			DeletedAt: sql.NullTime{
				Valid: true,
				Time:  time.Now(),
			},
		},
	}

	tx, err := db.Beginx()
	if err != nil {
		return fmt.Errorf("failed to init transaction: %w", err)
	}
	defer tx.Rollback() // no-op when tx has already been commited.

	err = entityRepo.UpdateEntities(ctx, tx, updatedEntities)
	if err != nil {
		return err
	}
	return tx.Commit()
}

func main() {
	if err := run(); err != nil {
		fmt.Fprintf(os.Stderr, "error: %s\n", err.Error())
		os.Exit(1)
	}
}
```


---

#### Handling constraint violations

```sql
 create table
  users (
    user_id uuid default gen_random_uuid (),
    email text,
    primary key (user_id),
    constraint email_unique unique (email) -- ensure constraints have names
  );
```

```go
import (
	"errors"
	"fmt"

	"github.com/google/uuid"
	"github.com/jmoiron/sqlx"
	"github.com/lib/pq"
)

type UserEntity struct {
	UserId string `db:"user_id"`
	Email  string `db:"email"`
}

func CreateUser(db *sqlx.DB, user UserEntity) (UserEntity, error) {
	stmt := `
insert into
  users (user_id, email)
values
  ($1, $2)		
returning *
	`

	var u UserEntity
	err := db.QueryRowx(stmt, user.UserId, user.Email).StructScan(&u)
	var pgError error
	if err != nil {
		e := err.(*pq.Error)
		switch e.Constraint {
		case "email_unique":
			pgError = errors.New("user with the provided email address already exists")

		default:
			pgError = errors.New("failed to create user")
		}
	}

	return u, pgError
}

func run() error {
	db, err := sqlx.Open("postgres", CONN_STRING)
	if err != nil {
		return err
	}
	defer db.Close()

	if err := db.Ping(); err != nil {
		return fmt.Errorf("failed to ping database. Details: %s\n", err.Error())
	}

	newUserData := UserEntity{
		UserId: uuid.New().String(),
		Email:  "admin@site.com",
	}

	user, err := CreateUser(db, newUserData)
	if err != nil {
		return err
	}

	fmt.Printf("%+v\n", user)
	return nil
}
```