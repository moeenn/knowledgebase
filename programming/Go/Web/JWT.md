```go
package authToken

import (
	"fmt"
	"time"

	"github.com/golang-jwt/jwt/v5"
)

type TokenPayload struct {
	Id    string
	Email string
	Role  string
}

type JwtConfig struct {
	Issuer string
	Secret string
	Expiry time.Duration
}

func CreateToken(payload *TokenPayload, config *JwtConfig) (string, error) {
	claims := jwt.NewWithClaims(jwt.SigningMethodHS256, jwt.MapClaims{
		"userId": payload.Id,
		"sub":    payload.Email,
		"iss":    config.Issuer,
		"aud":    payload.Role,
		"exp":    time.Now().Add(config.Expiry).Unix(),
		"iat":    time.Now().Unix(), // Issued at
	})

	tokenString, err := claims.SignedString([]byte(config.Secret))
	if err != nil {
		return "", err
	}

	return tokenString, nil
}

func VerifyToken(tokenString string, config *JwtConfig) (*TokenPayload, error) {
	token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
		return []byte(config.Secret), nil
	})

	if err != nil {
		return nil, err
	}

	if !token.Valid {
		return nil, fmt.Errorf("invalid token")
	}

	email, err := token.Claims.GetSubject()
	if err != nil {
		return nil, err
	}

	role, err := token.Claims.GetAudience()
	if err != nil || len(role) == 0 {
		return nil, err
	}

	claimsMap, ok := token.Claims.(jwt.MapClaims)
	if !ok {
		return nil, fmt.Errorf("invalid token claims")
	}

	userId, ok := claimsMap["userId"].(string)
	if !ok {
		return nil, fmt.Errorf("invalid token claims")
	}

	expiry, err := token.Claims.GetExpirationTime()
	if err != nil {
		return nil, err
	}

	if time.Now().After(expiry.Time) {
		return nil, fmt.Errorf("token expired")
	}

	tokenPayload := TokenPayload{
		Id:    userId,
		Email: email,
		Role:  role[0],
	}

	return &tokenPayload, nil
}
```

```go
package authToken

import (
	"testing"
	"time"

	"github.com/google/uuid"
	"github.com/stretchr/testify/assert"
)

func TestTokenCreateVerify(t *testing.T) {
	testUser := TokenPayload{
		Id:    uuid.NewString(),
		Email: "some-test-user@site.com",
		Role:  "ADMIN",
	}

	config := JwtConfig{
		Issuer: "sample.com",
		Secret: "some-super-secret-token",
		Expiry: time.Hour,
	}

	token, err := CreateToken(&testUser, &config)
	assert.NoError(t, err)
	assert.NotEqual(t, token, "")

	payload, err := VerifyToken(token, &config)
	assert.NoError(t, err)
	assert.Equal(t, payload.Id, testUser.Id)
	assert.Equal(t, payload.Email, testUser.Email)
	assert.Equal(t, payload.Role, testUser.Role)
}
```