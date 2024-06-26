#### To-do

- [ ] Storing of fields in DB
	- [ ] Long / Integer
	- [ ] Boolean
	- [ ] String
	- [ ] `LocalDateTime`
	- [ ] `LocalDate`
	- [ ] `LocalTime`
	- [ ] `Optional`

- [x] `ResponseEntity<T>`
- [x] `@Controller` vs `@RestController`
- [ ] `@CrudRepository` vs `@JpaRepository`
- [ ] `@ControllerAdvice` vs `@RestControllerAdvice`
- [ ] Common mistakes [Link](https://www.youtube.com/watch?v=PbkROQPTBao&list=WL&index=5)


---

#### Reference Docs
Official Reference Docs [Link](https://docs.spring.io/spring-boot/docs/3.2.5/reference/htmlsingle/index.html)


---

#### Simple CRUD example

```java
import jakarta.persistence.*;

@Entity
@Table(name = "users")
public class User {
    @Id
    @GeneratedValue(strategy = GenerationType.AUTO)
    Long id;

    @Column(nullable = false, unique = true)
    String email;

    @Column(nullable = false)
    String password;

    public User() {}

    public User(Long id, String email, String password) {
        this.email = email;
        this.id = id;
        this.password = password;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", email='" + email + '\'' +
                ", password='" + password + '\'' +
                '}';
    }
}
```

```java
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface UserRepository extends JpaRepository<User, Long> { }
```

```java
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class UserService {
    @Autowired
    private UserRepository userRepository;

    public Optional<User> findById(Long id) {
        return userRepository.findById(id);
    }

    public List<User> allUsers() {
        return userRepository.findAll();
    }

    public User addUser(UserCreateUpdateDTO dto) {
        return userRepository.save(dto.toUser());
    }

    public boolean deleteUser(Long id) {
        Optional<User> user = userRepository.findById(id);
        if (user.isEmpty()) {
            return false;
        }

        userRepository.delete(user.get());
        return true;
    }
}
```

```java
import com.example.api.exceptions.NotFoundException;
import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

@Validated
@RestController
@RequestMapping("/api/v1/user")
public class UserController {
    @Autowired
    private UserService userService;

    @GetMapping("{id}")
    public User getUser(@PathVariable Long id) throws NotFoundException {
        var user = userService.findById(id);
        if (user.isEmpty()) {
            throw new NotFoundException("user not found");
        }

        return user.get();
    }

    @GetMapping
    public UserListDTO allUsers() {
        var users = userService.allUsers();
        return new UserListDTO(users);
    }

    @PostMapping
    public User addUser(@Valid @RequestBody UserCreateUpdateDTO body) {
        return userService.addUser(body);
    }

    @DeleteMapping("{id}")
    public void deleteUser(@PathVariable Long id) throws NotFoundException {
        boolean isDeleted = userService.deleteUser(id);
        if (!isDeleted) {
            throw new NotFoundException("user not found");
        }
    }
}
```

```java
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;

public class UserCreateUpdateDTO {
    @NotNull
    @NotBlank(message = "Email address is required")
    @Email(message = "Please provide a valid email address")
    private String email;

    @NotNull
    @NotBlank(message = "Password is required")
    @Size(min = 8, message = "Password must be at least 8 characters in length")
    private String password;

    public UserCreateUpdateDTO(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String toString() {
        return "UserCreateUpdateDTO{" +
                "email='" + email + '\'' +
                ", password='" + password + '\'' +
                '}';
    }

    public User toUser() {
        User user = new User();
        user.setEmail(email);
        user.setPassword(password);
        return user;
    }
}
```

```java
import java.util.List;

public record UserListDTO(
    List<User> users
) { }
```


---

#### Exception Handling

```java
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ResponseStatus;

@ResponseStatus(value = HttpStatus.NOT_FOUND)
public class NotFoundException extends Exception {
    public NotFoundException(String message) {
        super(message);
    }
}
```

```java
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;

import java.util.HashMap;
import java.util.Map;

@ControllerAdvice
public class NotFoundAdvice {
    @ResponseBody
    @ExceptionHandler(NotFoundException.class)
    @ResponseStatus(HttpStatus.NOT_FOUND)
    public Map<String, String> notFoundHandler(NotFoundException ex) {
        Map<String, String> errors = new HashMap<>();
        errors.put("error", ex.getMessage());
        return errors;
    }
}
```


---

##### Handling validation Exceptions

```java
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.MethodArgumentNotValidException;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

import java.util.HashMap;

@RestControllerAdvice
public class GlobalExceptionHandler {
    @ExceptionHandler(MethodArgumentNotValidException.class)
    public ResponseEntity<ValidationException> handleValidationErrors(MethodArgumentNotValidException ex) {
        ValidationException result = new ValidationException(new HashMap<>());
        ex.getBindingResult().getFieldErrors().forEach(
                error -> result.addError(error.getField(), error.getDefaultMessage()));

        return new ResponseEntity<ValidationException>(result, new HttpHeaders(), HttpStatus.UNPROCESSABLE_ENTITY);
    }
}
```

```java
import java.util.Map;

public class ValidationException {
    private final Map<String, String> error;

    public ValidationException(Map<String, String> error) {
        this.error = error;
    }

    public Map<String, String> getError() {
        return error;
    }

    public void addError(String key, String error) {
        this.error.put(key, error);
    }
}
```


---

#### `@Controller` vs `@RestController`

`Controller` annotation comes from the traditional Spring MVC it required that all response bodies be annotated with `@ResponseBody` as below.

```java
@Controller
@RequestMapping("books")
public class SimpleBookController {

    @GetMapping("/{id}", produces = "application/json")
    public @ResponseBody Book getBook(@PathVariable int id) {
        return findBookById(id);
    }
}
```

`RestController` annotation combines `Controller` and `ResponseBody` annotations. Using it, we don't need to specify `ResponseBody` on controller method returns.

```java
@RestController
@RequestMapping("books-rest")
public class SimpleBookRestController {
    @GetMapping("/{id}", produces = "application/json")
    public Book getBook(@PathVariable int id) {
        return findBookById(id);
    }
}
```


---

#### ResponseEntity

`ResponseEntity<T>` represents the entire response object. It can include the generic body, status code and headers. It's basic usage can look like this.

```java
@Controller
@RequestMapping("/user")
public class UserController {
  @GetMapping("")
  public ResponseEntity<User> sample() {
    var user = new User(10L, "admin@site.com", true);
    return new ResponseEntity<>(user, HttpStatus.CREATED);
  }
}
```

```java
 return ResponseEntity.status(HttpStatus.CREATED).body(user);
```

```java
// return with status code 200
return ResponseEntity.ok(user);
```

Headers can be included in the response entity as follows.

```java
@Controller
@RequestMapping("/user")
public class UserController {
  @GetMapping("")
  public ResponseEntity<User> sample() {
    var user = new User(10L, "admin@site.com", true);
    var headers = new HttpHeaders();
    headers.add("Custom-header-X", "foo");
    headers.add("Custom-header-Y", "bar");

    return new ResponseEntity<>(user, headers, HttpStatus.CREATED);
  }
}
```

```java
// include multiple headers
return ResponseEntity
  .badRequest()
  .headers(headers)
  .body(user);
```

```java
// include single header
return ResponseEntity
  .ok()
  .header("Custom-header-X", "value")
  .body(user);
```


---

