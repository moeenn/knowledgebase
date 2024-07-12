```go
package main

import (
  "fmt"
  "os"
  "strings"
)

func main() {
  err := os.Setenv("LINUX", "Ubuntu")
  if err != nil {
    fmt.Printf("error: %s\n", err.Error())
    return
  }
  
  fmt.Println("LINUX: ", os.Getenv("LINUX"))

  // check if env Variable is set
  if system := os.Getenv("SYSTEM"); len(system) > 0 {
    fmt.Println("SYSTEM: ", system)
  }

  // get all environment variables
  for _, e := range os.Environ() {
    var pair []string = strings.Split(e, "=")
    fmt.Println(pair)
  }
}
```


#### Loading Environment variables from a file

```bash
$ go install -v github.com/joho/godotenv/cmd/godotenv@latest
```

```bash
$ godotenv -f .env go run .
```


#### Using external package

```go
package main

import (
  "fmt"

  "github.com/caarlos0/env/v11"
)

type EnvConfig struct {
  DatabaseURI string `env:"DATABASE_URI,notEmpty"`
  JWTSecret   string `env:"JWT_SECRET,notEmpty"`
}

type DatabaseConfig struct {
  URI string
}

type AuthConfig struct {
  JWTSecret string
}

type Config struct {
  Database DatabaseConfig
  Auth     AuthConfig
}

func NewConfig() (*Config, error) {
  envConfig := &EnvConfig{}
  opts := env.Options{RequiredIfNoDef: true} // all fields will be mandatory

  if err := env.ParseWithOptions(envConfig, opts); err != nil {
    return &Config{}, err
  }

  config := &Config{
    Database: DatabaseConfig{
      URI: envConfig.DatabaseURI,
    },
    Auth: AuthConfig{
      JWTSecret: envConfig.JWTSecret,
    },
  }

  return config, nil
}

func main() {
  config, err := NewConfig()
  if err != nil {
    fmt.Printf("error loading environment configuration: %s\n", err.Error())
    return
  }

  fmt.Printf("%+v\n", config)
}
```
