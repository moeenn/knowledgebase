```go
package jwt

import (
	"errors"
	"time"

	"github.com/golang-jwt/jwt/v5"
)

type JWTPayload struct {
	UserId   string
	UserRole string
}

type TokenResult struct {
	Token  string
	Expiry int64
}

func GenerateToken(secret string, expMinutes uint, payload JWTPayload) (*TokenResult, error) {
	expiry := time.Now().Add(time.Minute * time.Duration(expMinutes)).Unix()

	t := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
		"iss": payload.UserId,
		"sub": payload.UserRole,
		"exp": expiry,
	})

	s, err := t.SignedString([]byte(secret))
	if err != nil {
		return &TokenResult{}, err
	}

	return &TokenResult{Token: s, Expiry: expiry}, nil
}

func ValidateToken(secret string, token string) (JWTPayload, error) {
	parsed, err := jwt.Parse(token, func(token *jwt.Token) (interface{}, error) {
		return []byte(secret), nil
	})

	if err != nil || !parsed.Valid {
		return JWTPayload{}, errors.New("Invalid or expired JWT")
	}

	userId, err := parsed.Claims.GetIssuer()
	if err != nil {
		return JWTPayload{}, errors.New("Invalid or expired JWT")
	}

	userRole, err := parsed.Claims.GetSubject()
	if err != nil {
		return JWTPayload{}, errors.New("Invalid or expired JWT")
	}

	payload := JWTPayload{
		UserId:   userId,
		UserRole: userRole,
	}

	return payload, nil
}
```

```go
package jwt

import (
	"testing"

	"github.com/google/uuid"
)

func TestGenerateAndValidate(t *testing.T) {
	key := "some_random_secret_key"
	var expMinutes uint = 15

	payload := JWTPayload{
		UserId:   uuid.New().String(),
		UserRole: "ADMIN",
	}

	token, err := GenerateToken(key, expMinutes, payload)
	if err != nil {
		t.Errorf("failed to generate token")
	}

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

	if decodedPayload.UserRole != payload.UserRole {
		t.Errorf("unexpected user role in payload. Expected: %s, Got: %s",
			payload.UserRole,
			decodedPayload.UserRole,
		)
	}
}
```