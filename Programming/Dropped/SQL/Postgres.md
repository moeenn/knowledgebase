
##### Databases

```sql
-- create an new database
CREATE DATABASE sample;

-- delete a database
DROP DATABASE sample;
```

```bash
# create new db using PostgreSQL shell
$ psql -h <Host> -p <Port> -U <User> <database> --command="CREATE DATABASE <db_name> WITH OWNER <User>"
```

---

#### Column Data types

| Type | Description |  
| -------: | :------ |  
| `INT` | Signed four-byte integer |
| `BIGINT` | Signed eight-byte integer |
| `BOOL` | Logical Boolean (true/false) |
| `CHAR (n)` | Fixed-length character string |
| `VARCHAR (n)` | Variable-length character string |
| `TEXT` | Variable-length character string |
| `UUID` | Universally unique identifier |
| `DATE` | Calendar date (year, month, day) |
| `FLOAT8` | Double precision floating-point number (8 bytes) |
| `INET` | IPv4 or IPv6 host address |
| `INTERVAL` | Time span |
| `JSON` | Textual JSON data |
| `JSONB` | Binary JSON data, decomposed |
| `SMALLINT` | Signed two-byte integer |
| `SERIAL` | Auto Incrementing four-byte integer |
| `BIGSERIAL` | Auto Incrementing eight-byte integer |
| `TIME` | Time of day (no time zone) |
| `TIMETZ` | Time of day, including time zone |
| `TIMESTAMP` | Date and time (no time zone) |
| `TIMESTAMPTZ` | Date and time, including time zone |


---

#### Constraints

| Type | Description |  
| -------: | :------ |  
| `NOT NULL` | Column value is mandatory |
| `UNIQUE` | The value in the column must be unique |
| `DEFAULT` | Specify a default value in case a value is not provided by the user |
| `PRIMARY KEY` | Set column and the primary key for the table |
| `REFERENCES other_table(other_column)` | Add foreign key constraint |


---
##### Tables

In SQL it is a convention that table names should be snake-case plurals.

```sql
-- create a new table within a database
CREATE TABLE
  users (
    user_id SERIAL,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    location POINT NOT NULL,
    PRIMARY KEY (user_id)
  );
```

`UUID` can be used as Primary key as follows.

```sql
CREATE TABLE users (
  user_id UUID DEFAULT gen_random_uuid(),
  name VARCHAR(100) NOT NULL,
  active BOOL DEFAULT (TRUE),
  
  PRIMARY KEY (user_id)
);
```

All Existing tables can also be deleted using the following query. 

```sql
DROP SCHEMA public CASCADE;
CREATE SCHEMA public;
```

---

#### Insert Data into Table

```sql
-- insert multiple records into table
INSERT INTO
  users (name, email, dob, location)
VALUES
  (
    'User one',
    'user_one@site.com',
    DATE '1990-02-10',
    POINT '(30.44, 50.23)'
  ),
  (
    'User two',
    'user_two@site.com',
    DATE '1998-09-17',
    POINT '(30.44, 50.23)'
  );
```

```sql
-- insert into multiple tables
WITH password_insert AS (
  INSERT INTO password (hash)
  VALUES ('abc123223213')
  RETURNING id 
)

INSERT INTO
  users (email, role, password_id)
  VALUES ('admin@site.com', 'ADMIN', (select id from password_insert));
```


---

#### Enumerations

```sql
CREATE TYPE
  user_role AS ENUM('ADMIN', 'USER');

CREATE TABLE
  users (
    user_id SERIAL,
    email VARCHAR(255) UNIQUE NOT NULL,
    role user_role NOT NULL,
    password VARCHAR(255),
    PRIMARY KEY (user_id)
  );

INSERT INTO
  users (email, role)
VALUES
  ('admin@site.com', user_role 'ADMIN');
```


---

#### Relationships

##### One-to-one

```sql
-- table schema
CREATE TABLE
  profiles (
    profile_id SERIAL,
    name VARCHAR(255),
    PRIMARY KEY (profile_id)
  );

CREATE TABLE
  users (
    user_id SERIAL,
    email VARCHAR(255) UNIQUE NOT NULL,
    -- notice the unique constraint (1:1)
    profile_id SERIAL UNIQUE NOT NULL,
    PRIMARY KEY (user_id),
    FOREIGN KEY (profile_id) REFERENCES profiles (profile_id)
  );

-- insert dummy data
WITH
  profile_insert AS (
    INSERT INTO
      profiles (name)
    VALUES
      ('User One')
    RETURNING
      profile_id
  )
INSERT INTO
  users (email, profile_id)
VALUES
  (
    'user@site.com',
    (
      SELECT
        profile_id
      FROM
        profile_insert
    )
  );

-- fetch data through users table
SELECT
  users.user_id,
  users.email,
  profiles.name
FROM
  users
  JOIN profiles ON users.profile_id = profiles.profile_id;

-- fetch data through profiles table
SELECT
  profiles.profile_id,
  users.user_id,
  users.email,
  profiles.name
FROM
  profiles
  JOIN users ON profiles.profile_id = users.profile_id
WHERE
  profiles.profile_id = 2;
```


##### One-to-many

```sql
-- table schema
CREATE TABLE
  users (
    user_id SERIAL,
    email VARCHAR(100),
    PRIMARY KEY (user_id)
  );

CREATE TABLE
  posts (
    post_id SERIAL,
    title VARCHAR(100) UNIQUE,
    -- notice user_id has no unique constraint (1:M)
    user_id SERIAL NOT NULL,
    PRIMARY KEY (post_id),
    FOREIGN KEY (user_id) REFERENCES users (user_id)
  );

-- insert dummy data
INSERT INTO
  users (email)
VALUES
  ('admin@site.com');

WITH
  user_insert AS (
    INSERT INTO
      users (email)
    VALUES
      ('user@site.com')
    RETURNING
      user_id
  )
INSERT INTO
  posts (title, user_id)
VALUES
  (
    'post one',
    (
      SELECT
        user_id
      FROM
        user_insert
    )
  ),
  (
    'post two',
    (
      SELECT
        user_id
      FROM
        user_insert
    )
  );

-- fetch related records
SELECT
  users.user_id,
  users.email,
  posts.title
FROM
  users
  JOIN posts ON users.user_id = posts.user_id
WHERE
  users.user_id = 2;
```


##### Many-to-many

```sql
 -- schena definitions
CREATE TABLE
  roles (
    role_id SERIAL NOT NULL,
    role_name VARCHAR (100) NOT NULL,
    PRIMARY KEY (role_id)
  );

CREATE TABLE
  users (
    user_id SERIAL NOT NULL,
    email VARCHAR (255) UNIQUE NOT NULL,
    password VARCHAR (255),
    PRIMARY KEY (user_id)
  );

CREATE TABLE
  user_roles (
    user_role_id SERIAL NOT NULL,
    user_id SERIAL NOT NULL,
    role_id SERIAL NOT NULL,
    PRIMARY KEY (user_role_id),
    FOREIGN KEY (user_id) REFERENCES users (user_id),
    FOREIGN KEY (role_id) REFERENCES roles (role_id)
  );

-- insert test data
INSERT INTO
  roles (role_name)
VALUES
  ('admin'),
  ('customer'),
  ('user');

INSERT INTO
  users (email)
VALUES
  ('admin_one@site.com'),
  ('admin_two@site.com'),
  ('user@site.com'),
  ('customer@site.com');

INSERT INTO
  user_roles (user_id, role_id)
VALUES
  (1, 1),
  (2, 1),
  (3, 3),
  (4, 2);

-- query: get all admins
SELECT
  users.user_id,
  users.email,
  roles.role_name
FROM
  users
  INNER JOIN user_roles ON users.user_id = user_roles.user_id
  INNER JOIN roles ON user_roles.role_id = roles.role_id
WHERE
  roles.role_name = 'admin';
```