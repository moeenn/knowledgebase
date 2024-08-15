
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