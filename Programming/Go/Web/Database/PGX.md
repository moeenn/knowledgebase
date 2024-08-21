
```go
package main

import (
	"context"
	"encoding/json"
	"fmt"

	"github.com/jackc/pgx/v5"
	"github.com/jackc/pgx/v5/pgxpool"
)

// NOTE: in this example, we are using the database entities as DTOs as well
// i.e. the same structs have both `db` and `json` tags.
// Ideally, we will use different stucts as entities and DTOs. This is beneficial
// in the long-run because even for a slighly complex application, the db entities
// will be quite different from the DTOs.
type UserEntity struct {
	UserId string `db:"user_id" json:"user_id"`
	Email  string `db:"email" json:"email"`
}

type PostEntity struct {
	PostId string `db:"post_id" json:"post_id"`
	Title  string `db:"title" json:"title"`
}

type UserEntityWithPosts struct {
	UserId string       `db:"user_id" json:"user_id"`
	Email  string       `db:"email" json:"email"`
	Posts  []PostEntity `db:"posts" json:"posts"`
}

const (
	CONN_STRING = "postgresql://devuser:devpass@localhost:5432/dev"
)

func ConnectDB(ctx context.Context, connectionURI string) (
	*pgxpool.Pool, error) {
	// pgx also provides a pgx.Connect function for establishing database
	// connection. However, that is not thread-safe. In any production web
	// application, we need thread-safety between different requests.
	// pgxpool.Pool is thread-safe and MUST ALlWAYS be used in web APIs.
	db, err := pgxpool.New(ctx, connectionURI)
	if err != nil {
		return nil, err
	}

	if err := db.Ping(ctx); err != nil {
		return nil, fmt.Errorf(
			"failed to ping database. Details: %s\n", err.Error())
	}

	return db, nil
}

func GetUserWithPosts(ctx context.Context, db *pgxpool.Pool) (
	[]UserEntityWithPosts, error) {

	query := `
select
  users.user_id,
  users.email,
  jsonb_agg (posts) filter (where posts.user_id is not null) as posts
from
  users
  left join posts on users.user_id = posts.user_id
group by
  users.user_id		
	`

	rows, err := db.Query(ctx, query)
	defer rows.Close()
	var nilResult []UserEntityWithPosts

	if err != nil {
		return nilResult, err
	}

	result, err := pgx.CollectRows(
		rows,
		pgx.RowToStructByName[UserEntityWithPosts],
	)

	if err != nil {
		return nilResult, err
	}

	return result, nil
}

func run() error {
	ctx := context.Background()
	db, err := ConnectDB(ctx, CONN_STRING)
	if err != nil {
		return err
	}
	defer db.Close()

	result, err := GetUserWithPosts(ctx, db)
	if err != nil {
		return err
	}

	encoded, err := json.Marshal(result)
	if err != nil {
		return err
	}

	fmt.Printf("%s\n", encoded)
	return nil
}

func main() {
	if err := run(); err != nil {
		fmt.Printf("Error: %s\n", err.Error())
	}
}
```


#### Handling constraint violations

```go
func CreateUser(ctx context.Context, db *pgxpool.Pool, user UserEntity) (
UserEntity, error) {

	stmt := `
		insert into users (user_id, email)
		values (@userId, @email)
	`

	_, err := db.Exec(ctx, stmt, pgx.NamedArgs{
		"userId": user.UserId,
		"email":  user.Email,
	})

	if err != nil {
		var nilResult UserEntity
		var pgError *pgconn.PgError

		if errors.As(err, &pgError) {
			switch pgError.ConstraintName {
			case "email_unique":
				return nilResult, fmt.Errorf("user with the provided email address already exists")

			// other constraints will go here
			}
		} else {
			return nilResult, err
		}
	}

	return user, nil
}
```

