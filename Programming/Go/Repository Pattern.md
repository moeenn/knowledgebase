
```go
type Repository[T any] interface {
	All() []T
	GetById(id string) (T, error)
	Add(record T) error
	Update(id string, value T) (T, error)
	Delete(id string) error
}

type User struct {
	// map model columns
}

type UserRepository struct {
	// provide concrete implementation of all methods inside Repository[T]
	// IMPORTANT: never return implementation specific errors and only return
	// generic errors from repo methods
}

func (ur *UserRepository) All() []User {
	return []User{} // TODO
}

func (ur *UserRepository) GetById(id string) (User, error) {
	return User{}, nil // TODO
}

func (ur *UserRepository) Add(user User) error {
	return nil
}

func (ur *UserRepository) Update(id string, value User) (User, error) {
	return User{}, nil // TODO
}

func (ur *UserRepository) Delete(id string) error {
	return nil // TODO
}

type UserService struct {
	UserRepo Repository[User]
}

func main() {
	userService := UserService{
		UserRepo: &UserRepository{},
	}

    // TODO: do something with the service
}
```