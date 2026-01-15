
```bash
$ sudo apt-get install -y ocaml opam
$ opam init
$ opam switch create default ocaml-base-compiler.5.3.0
$ opam install -y utop odoc ounit2 qcheck bisect_ppx menhir ocaml-lsp-server ocamlformat
```

```bash
# list defined switches.
$ opam switch list

# remove switch. 
$ opam switch remove <name>
```

```bash
# create a new project.
$ dune init project <project-name>

# build project.
$ dune build

# run binary (binary ext is always .exe, even on linux).
$ ./_build/default/bin/main.exe
```

**Tip**: Disable warnings for unused declarations.

```dune
(flags
  (:standard -w -27-32))
```


---

#### Hello world

```ml
(* function without name serves as the entry-point. *)
let () =
	let name = "User" in 
	print_endline name
```


---

#### A simple program

```ml
open Printf

module UserRole = struct
  type t = Admin | Customer | Employee

  let to_string role =
    match role with
    | Admin -> "Admin"
    | Customer -> "Customer"
    | Employee -> "Employee"

  let from_string input =
    match input with
    | "Admin" -> Some Admin
    | "Customer" -> Some Customer
    | "Employee" -> Some Employee
    | _ -> None
end

module User = struct
  type t = { id : string; email : string; role : UserRole.t }

  let create id email role = { id; email; role }

  let to_string user =
    sprintf "User{id=%s, email=%s, role=%s}" user.id user.email
      (UserRole.to_string user.role)
end

module UserRepo = struct
  type t = { users : User.t list }

  let create = { users = [] }
  let add_user ~user repo = { users = user :: repo.users }

  let remove_user ~userId repo =
    let predicate (user : User.t) = user.id != userId in
    { users = List.filter predicate repo.users }
end

let () =
  let userRepo : UserRepo.t =
    UserRepo.create
    |> UserRepo.add_user ~user:(User.create "10" "Mr. Admin" UserRole.Admin)
    |> UserRepo.add_user
         ~user:(User.create "20" "Mr. Customer" UserRole.Customer)
    |> UserRepo.add_user
         ~user:(User.create "30" "Mr. Employee" UserRole.Employee)
    |> UserRepo.remove_user ~userId:"10"
  in

  List.map (fun user -> User.to_string user) userRepo.users
  |> List.iter print_endline
```

**Note**
- `open` brings module components into the current module scope. In the above example `printf` and `sprintf` functions are defined inside `Printf` module. We can use these function like `Printf.sprintf` as well.
- The pipe operator passes the value as the last function argument (unlike Elixir where it is passed as the first argument).