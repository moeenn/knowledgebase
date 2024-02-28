
```go
package main

import (
	"fmt"

	"github.com/go-playground/validator/v10"
)

func NewErrorMap(errors error) (result map[string][]string, ok bool) {
	result = make(map[string][]string)

	if errors == nil {
		return result, true
	}

	vErrors, ok := errors.(validator.ValidationErrors)
	if !ok {
		panic("invalid errors object provided")
	}

	for _, err := range vErrors {
		ok = false
		message := GetMessage(err.Tag(), err.Param())
		current, exists := result[err.Field()]
		if !exists {
			result[err.Field()] = []string{}
		}

		result[err.Field()] = append(current, message)
	}

	return result, ok
}

func GetMessage(tag string, param string) string {
	switch tag {
	case "required":
		return "Please provide a value for this field"

	case "email":
		return "Please provide a valid email address"

	case "uuid4":
		return "Please provide a valid UUID"

	case "min":
		return fmt.Sprintf("Value must be minimum length of %s", param)

	case "max":
		return fmt.Sprintf("Value must be maximum length of %s", param)

	default:
		return "Please provide a valid value"
	}
}

func DebugValidationError(err validator.FieldError) {
	fmt.Println("namespace\t", err.Namespace())
	fmt.Println("field\t\t", err.Field())
	fmt.Println("struct-ns\t", err.StructNamespace())
	fmt.Println("struct-field\t", err.StructField())
	fmt.Println("tag\t", err.Tag())
	fmt.Println("actual-tag\t", err.ActualTag())
	fmt.Println("kind\t", err.Kind())
	fmt.Println("type\t", err.Type())
	fmt.Println("value\t", err.Value())
	fmt.Printf("param\t%s\n\n", err.Param())
}

type User struct {
	Id       string `validate:"required,uuid4"`
	Email    string `validate:"required,email"`
	Password string `validate:"required,min=8"`
}

func main() {
	user := User{
		Id:       "6796c637-a60a-4934-998e-0f7fe1f2f2ca",
		Email:    "admin@site.com",
		Password: "123_Apple",
	}

	validate := validator.New(validator.WithRequiredStructEnabled())
	messages, ok := NewErrorMap(validate.Struct(user))
	if !ok {
		for k, v := range messages {
			fmt.Printf("%s\n%v\n\n", k, v)
		}
		return
	}

	fmt.Println("-- valid --")
}
```