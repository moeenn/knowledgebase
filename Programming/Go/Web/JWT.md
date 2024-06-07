```go
package jwt

import (
	"errors"
	"time"

	"github.com/golang-jwt/jwt/v5"
)

type JWTPayload struct {
	UserId    string
	UserRoles []string
}

type TokenResult struct {
	Token  string
	Expiry int64
}

func GenerateToken(secret string, expMinutes uint, payload JWTPayload) (*TokenResult, error) {
	expiry := time.Now().Add(time.Minute * time.Duration(expMinutes)).Unix()

	t := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
		"sub": payload.UserId,
		"aud": payload.UserRoles,
		"exp": expiry,
	})

	s, err := t.SignedString([]byte(secret))
	if err != nil {
		return &TokenResult{}, err
	}

	return &TokenResult{Token: s, Expiry: expiry}, nil
}

func ValidateToken(secret string, token string) (*JWTPayload, error) {
	errMessage := errors.New("invalid or expired JWT")
	payload := &JWTPayload{}

	parsed, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		return []byte(secret), nil
	})

	if err != nil || !parsed.Valid {
		return payload, errMessage
	}

	userId, err := parsed.Claims.GetSubject()
	if err != nil || userId == "" {
		return payload, errMessage
	}

	userRoles, err := parsed.Claims.GetAudience()
	if err != nil {
		return payload, errMessage
	}

	payload.UserId = userId
	payload.UserRoles = userRoles

	return payload, nil
}
```

```go
package jwt

import (
	"fmt"
	"testing"

	"github.com/google/uuid"
)

func TestGenerateAndValidate(t *testing.T) {
	key := "some_random_secret_key"
	var expMinutes uint = 15

	payload := JWTPayload{
		UserId:    uuid.New().String(),
		UserRoles: []string{"ADMIN"},
	}

	token, err := GenerateToken(key, expMinutes, payload)
	if err != nil {
		t.Errorf("failed to generate token")
	}

	fmt.Printf("token: %v\n", token)

	decodedPayload, err := ValidateToken(key, token.Token)
	if err != nil {
		t.Errorf("failed to decode token")
	}

	if decodedPayload.UserId != payload.UserId {
		t.Errorf("unexpected user id in payload. Expected: %s, Got: %s",
			payload.UserId,
			decodedPayload.UserId,
		)
	}

	numRoles := len(decodedPayload.UserRoles)
	if numRoles != 1 {
		t.Errorf("invalid number of decoded userRoles. Expected: %d, Got: %d", 1, numRoles)
	}

	if decodedPayload.UserRoles[0] != payload.UserRoles[0] {
		t.Errorf("unexpected user role in payload. Expected: %s, Got: %s",
			payload.UserRoles,
			decodedPayload.UserRoles,
		)
	}
}
```