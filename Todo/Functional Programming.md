
##### Referential transparency
An expression `e` is referentially transparent if for all programs `p`, all occurrences of `e` in `p`  
can be replaced by the result of evaluating `e` without affecting the meaning of `p`. The **substitution model** provides a way to test whether an expression  is referentially transparent.  

##### Side effect
A side effect is something a function does aside from simply returning a result.  
  
##### Procedures
Procedure is often used to refer to some parameterised chunk of code that may have side effects.  

##### Higher-order functions
Higher-order functions are functions that take other functions as arguments and may themselves return functions as their output.  
  
##### Tail-position call
A call is said to be in tail position if the caller does nothing other than return the value of the recursive call. If a recursive function is tail-call optimised, we prevent the risk of a stack overflow.  Tail recursion ensures the stack does not grow with each recursive call.

##### Monomorphic vs Polymorphic functions
A monomorphic functions, or functions that  operate on only one type of data. A polymorphic function, sometimes called a `Generic` function.  


---

#### Monads
Monads is a design pattern which allows user to chain operations while the monad manages secret work behind the scenes.

A monad has following components

1. A wrapper type e.g. `Wrapped<T>`
2. Wrap function: Turns `T` into `Wrapped<T>`

```ts
some<T> = (v: T) => Wrapped<T>
```

3. Run function: Runs transformations on the `Wrapped<T>` value.

```ts
run<T> = (
    input: Wrapped<T>,
    transform: (_: T) => Wrapped<T>
) => Wrapped<T>
```

##### Example

```ts
type User = {
  id: number;
  email: string;
  password: string | undefined;
};

function getUser(): User | undefined {
  return {
    id: 1,
    email: "admin@site.com",
    password: "password",
  };
}

function getUserPassword(user: User): string | undefined {
  if (!user.password) {
    return undefined;
  }
  return user.password;
}

function verifyUserPassword(password: string, clearText: string): boolean | undefined {
  if (password != clearText) {
    return undefined;
  }
  return true;
}

function processRequest(): boolean | undefined {
  const user: User | undefined = getUser();
  if (!user) {
    return undefined;
  }

  const password = getUserPassword(user);
  if (!password) {
    return undefined;
  }

  const matched = verifyUserPassword(password, "password");
  if (matched == undefined) {
    return undefined;
  }

  return matched;
}
```

This is fairly nasty code. It can be improved by introducing the `Option<T>` monad.

```ts
type Option<T> = T | undefined;

function run<T, E>(opt: Option<T>, transform: (v: T) => Option<E>): Option<E> {
  if (opt === undefined) {
    return undefined;
  }
  return transform(opt);
}
```

```ts
function getUser(): Option<User> {
  return {
    id: 1,
    email: "admin@site.com",
    password: "password",
  };
}

function getUserPassword(user: User): Option<string> {
  if (!user.password) {
    return undefined;
  }
  return user.password;
}

// curried function
function verifyUserPassword(clearText: string): (password: string) => Option<boolean> {
  return (password) => {
    if (password != clearText) {
      return undefined;
    }
    return true;
  }
}

function processRequest(): Option<boolean> {
  const user: Option<User> = getUser();
  const password: Option<string> = run(user, getUserPassword);
  const matched: Option<boolean> = run(password, verifyUserPassword("password"));
  return matched;
}
```