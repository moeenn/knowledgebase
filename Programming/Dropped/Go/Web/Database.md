
#### Running migrations

```bash
export MIGRATIONS_PATH = migrations
export DB_CONNECTION = postgresql://user:pass@localhost:5432/dev?sslmode=disable

# install golang-migrate
$ go install -tags 'postgres' github.com/golang-migrate/migrate/v4/cmd/migrate@latest

# create new migration file
$ migrate create -ext sql -dir ${MIGRATIONS_PATH} -seq migration_name

# run all pending migrations
$ migrate -path '${MIGRATIONS_PATH}' -database ${DB_CONNECTION} -verbose up

# clear database and drop all tables
$ migrate -database ${DB_CONNECTION} drop
```


#### Using `database/sql` package

```sql
CREATE TABLE IF NOT EXISTS
    users (
      user_id UUID UNIQUE NOT NULL,
      email VARCHAR (255) UNIQUE NOT NULL,
      password TEXT,
      PRIMARY KEY (user_id)  
    );
```

```go
package main

import (
	"database/sql"
	"fmt"
	"os"

	"github.com/google/uuid"
	_ "github.com/lib/pq"
)

type User struct {
	Id       string
	Email    string
	Password sql.NullString
}

func NewUser(email, password string) User {
	pwd := sql.NullString{
		String: password,
		Valid:  true,
	}

	return User{
		Id:       uuid.New().String(),
		Email:    email,
		Password: pwd,
	}
}

type UserRespository struct {
	db *sql.DB
}

func (r *UserRespository) CreateUser(user User) error {
	stmt := "INSERT INTO users (user_id, email, password) VALUES ($1, $2, $3)"
	_, err := r.db.Exec(stmt, user.Id, user.Email, user.Password)
	return err
}

func (r *UserRespository) AllUsers() []User {
	stmt := "SELECT * FROM users"
	rows, err := r.db.Query(stmt)
	if err != nil {
		return []User{}
	}
	defer rows.Close()

	users := []User{}
	for rows.Next() {
		user := User{}
		if err := rows.Scan(&user.Id, &user.Email, &user.Password); err != nil {
			return users
		}
		users = append(users, user)
	}

	return users
}

func (r *UserRespository) GetById(id string) (User, error) {
	stmt := "SELECT * FROM users WHERE user_id = $1"
	row := r.db.QueryRow(stmt, id)
	user := User{}

	if err := row.Scan(&user.Id, &user.Email, &user.Password); err != nil {
		return User{}, fmt.Errorf("user with id '%s' not found", id)
	}

	return user, nil
}

func (r *UserRespository) UpdateUser(user User) error {
	stmt := "UPDATE users SET email = $2, password = $3 WHERE user_id = $1"
	_, err := r.db.Exec(stmt, user.Id, user.Email, user.Password)
	return err
}

func (r *UserRespository) DeleteUser(id string) error {
	stmt := "DELETE FROM users WHERE user_id = $1"
	_, err := r.db.Exec(stmt, id)
	return err
}

func exit(message string) {
	fmt.Fprintf(os.Stderr, message+"\n")
	os.Exit(1)
}

func main() {
	// TODO: always read from env
	connString := "postgresql://devuser:devpass@localhost:5432/dev?sslmode=disable"
	db, err := sql.Open("postgres", connString)
	if err != nil {
		exit("failed to open database connection")
	}
	defer db.Close()

	if err := db.Ping(); err != nil {
		exit("failed to communicate with the database")
	}

	userRepo := UserRespository{db}

	user := NewUser("admin@site.com", "123_Apple")
	if err := userRepo.CreateUser(user); err != nil {
		exit("failed to create user: " + err.Error())
	}

	user.Email = "user@site.com"
	if err = userRepo.UpdateUser(user); err != nil {
		exit("failed to update user: " + err.Error())
	}

	fmt.Printf("-- done -- \n")
}
```

**Note on Placeholders**: Notice that the above SQL statements use `$n` as query placeholder values. This is specific to PostgreSQL. If using MySQL, use `?` as query placeholder.


#### Using `sqlx` package

```go
package main

import (
	"database/sql"
	"fmt"
	"os"

	"github.com/google/uuid"

	"github.com/jmoiron/sqlx"
	_ "github.com/lib/pq"
)

type User struct {
	Id       string         `db:"user_id"`
	Email    string         `db:"email"`
	Password sql.NullString `db:"password"`
}

func NewUser(email, password string) User {
	pwd := sql.NullString{
		String: password,
		Valid:  true,
	}

	return User{
		Id:       uuid.New().String(),
		Email:    email,
		Password: pwd,
	}
}

type UserRespository struct {
	db *sqlx.DB
}

func (r *UserRespository) CreateUser(user User) error {
	stmt := "INSERT INTO users (user_id, email, password) VALUES ($1, $2, $3)"
	_, err := r.db.Exec(stmt, user.Id, user.Email, user.Password)
	return err
}

func (r *UserRespository) AllUsers() []User {
	stmt := "SELECT * FROM users"
	users := []User{}

	if err := r.db.Select(&users, stmt); err != nil {
		return []User{}
	}

	return users
}

func (r *UserRespository) GetById(id string) (User, error) {
	stmt := "SELECT * FROM users WHERE user_id = $1"
	user := User{}

	if err := r.db.Get(&user, stmt, id); err != nil {
		return User{}, fmt.Errorf("user with id '%s' not found", id)
	}

	return user, nil
}

func (r *UserRespository) UpdateUser(user User) error {
	stmt := "UPDATE users SET email = $2, password = $3 WHERE user_id = $1"
	_, err := r.db.Exec(stmt, user.Id, user.Email, user.Password)
	return err
}

func (r *UserRespository) DeleteUser(id string) error {
	stmt := "DELETE FROM users WHERE user_id = $1"
	_, err := r.db.Exec(stmt, id)
	return err
}

func exit(message string) {
	fmt.Fprintf(os.Stderr, message+"\n")
	os.Exit(1)
}

func main() {
	// TODO: always read from env
	connString := "postgresql://user:pass@localhost:5432/dev?sslmode=disable"
	db, err := sqlx.Open("postgres", connString)
	if err != nil {
		exit("failed to open database connection")
	}
	defer db.Close()

	if err := db.Ping(); err != nil {
		exit("failed to communicate with the database")
	}

	userRepo := UserRespository{db}

	user := NewUser("admin@site.com", "123_Apple")
	if err := userRepo.CreateUser(user); err != nil {
		exit("failed to create user: " + err.Error())
	}

	user.Email = "user@site.com"
	if err = userRepo.UpdateUser(user); err != nil {
		exit("failed to update user: " + err.Error())
	}

	users := userRepo.AllUsers()
	fmt.Printf("%+v\n", users)
}
```
