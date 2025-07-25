
#### To-do
- [ ] Type casting
- [ ] Additional Features [Link](https://sive.rs/pg) 
- [ ] Volatile
- [ ] Triggers / Listen / Notify
- [ ] Partitioning [Link](https://rasiksuhail.medium.com/guide-to-postgresql-table-partitioning-c0814b0fbd9b)


---

#### Connecting to Database

##### Through `psql`

```bash
$ psql -h <hostname> -p <port> -d <database> -U <username>
```

##### Connection string 

```
postgresql://devuser:devpass@localhost:5432/dev?sslmode=disable
```


#### Exporting existing DB schema

```bash
pg_dump --schema-only --no-acl $DATABASE_URL > migrations/0000-init.sql
```


---

#### Comments

```sql
-- this style is used, as comments to document SQL statements
SELECT * FROM /* test */ users;
```


---

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


##### Drop all content of database

```sql
DROP SCHEMA public CASCADE;
CREATE SCHEMA public;
```


---

#### Column Data types

|            Type | Description                                                                                                                                                        |
| --------------: | :----------------------------------------------------------------------------------------------------------------------------------------------------------------- |
|           `INT` | Signed four-byte integer                                                                                                                                           |
|        `BIGINT` | Signed 64-Bit (i.e. 8-Byte) integer. Can be used to store money values in cents.                                                                                   |
|       `NUMERIC` | A number type with very high precision, supporting floating point numbers without the hassle of rounding-off errors. **The best choice for storing money values**. |
|          `BOOL` | Logical Boolean (`TRUE` / `FALSE`)                                                                                                                                 |
|      `CHAR (n)` | Fixed-length character string                                                                                                                                      |
|   `VARCHAR (n)` | Variable-length character string                                                                                                                                   |
|          `TEXT` | Variable-length character string                                                                                                                                   |
|          `UUID` | Universally unique identifier. Takes up 128-Bits of storage.                                                                                                       |
|          `DATE` | Calendar date (year, month, day)                                                                                                                                   |
|        `FLOAT8` | Double precision floating-point number (8 bytes). Avoid using in production because has precision problems                                                         |
| `DECIMAL(15,2)` | Store amount to exactly 2-decimal points. Used by most general ledger software                                                                                     |
|          `INET` | IPv4 or IPv6 host address                                                                                                                                          |
|      `INTERVAL` | Time span                                                                                                                                                          |
|          `JSON` | Textual JSON data                                                                                                                                                  |
|      `SMALLINT` | Signed 2-byte (16-bit) integer                                                                                                                                     |
|        `SERIAL` | Auto Incrementing 4-byte (32-bit) integer. Should **not** be used as primary key.                                                                                  |
|     `BIGSERIAL` | Auto Incrementing 8-byte (64-bit) integer. Can be used as primary keys.                                                                                            |
|          `TIME` | Time of day (no time zone)                                                                                                                                         |
|        `TIMETZ` | Time of day, including time zone                                                                                                                                   |
|     `TIMESTAMP` | Date and time (no time zone)                                                                                                                                       |
|   `TIMESTAMPTZ` | Date and time, including time zone                                                                                                                                 |


---

#### Constraints

|                                   Type | Description                                                         |
| -------------------------------------: | :------------------------------------------------------------------ |
|                             `NOT NULL` | Column value is mandatory                                           |
|                               `UNIQUE` | The value in the column must be unique                              |
|                              `DEFAULT` | Specify a default value in case a value is not provided by the user |
|                          `PRIMARY KEY` | Set column and the primary key for the table                        |
| `REFERENCES other_table(other_column)` | Add foreign key constraint                                          |
|                                `CHECK` | Boolean checks                                                      |
**Note**: If we provide proper names to our constraints, we will be able to catch errors properly when they are thrown by the database driver in case of constraint violations.

##### Example: Product price and discounted price

```sql
CREATE TABLE
  products (
    product_id BIGSERIAL,
    name TEXT NOT NULL,
    
    -- column level check
    price NUMERIC NOT NULL CHECK (price >= 0),
    discounted_price NUMERIC NOT NULL,
    PRIMARY KEY (product_id),
    
    -- table level check
    CONSTRAINT valid_discount CHECK (discounted_price < price)
  );
```


##### Example: Unique combinations

```sql
CREATE TABLE
  users (
    user_id UUID DEFAULT gen_random_uuid(),
    email TEXT,
    
    PRIMARY KEY (user_id),
    CONSTRAINT email_unique UNIQUE (email)
  );
```

```sql
CREATE TABLE
  user_profiles (
    user_id BIGSERIAL,
    profile_id BIGSERIAL,
    CONSTRAINT unique_user_id_profile_id UNIQUE (user_id, profile_id)
  );
```

**Note**: In this example we have applied a table level constraint which ensures that following
- `(1, 1)` and `(1, 2)` is allowed
- `(1, 1)` and `(1, 1)` in two separate rows is not allowed.


---
##### Tables

In SQL it is a convention that table names should be snake-case plurals.

```sql
-- create a new table within a database
CREATE TABLE
  users (
    user_id BIGSERIAL,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    location POINT NOT NULL,
    PRIMARY KEY (user_id)
  );
```


---

#### UUID
UUIDs can be used as unique identifiers for records. Here is how they work.

```sql
-- UUID as primary key, without default value
CREATE TABLE
  users (
    user_id UUID NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    PRIMARY KEY (user_id)
  );
```

```sql
-- UUID as primary key, with auto-generating UUIDs at insertion
CREATE TABLE
  users (
    user_id UUID DEFAULT gen_random_uuid(),
    email VARCHAR(255) UNIQUE NOT NULL,
    PRIMARY KEY (user_id)
  );
```

```sql
-- generating UUID at the time of insertion
INSERT INTO
  users (user_id, email)
VALUES
  (gen_random_uuid (), 'admin@site.com'),
  (gen_random_uuid (), 'user@site.com');
```


##### Why use `UUID` over `BIGSERIAL` as primary key?

- First question to ask is whether the record key should be random or sequential. 
- If record key is going to be exposed to the users, they random keys are more secure. Sequential keys can lead to enumeration attacks.

On the other hand, sequential keys have certain advantages as well

- They are faster to generate
- They are quick to index
- They take up less space than `UUID`

In summary, use `UUID` where security / entropy matters, otherwise default to using `BIGSERIAL` sequential keys.


---

#### Array Columns

```sql
-- table with array field
CREATE TABLE
  users (
    user_id BIGSERIAL,
    email VARCHAR(255) UNIQUE NOT NULL,
    phone_numbers VARCHAR(255) ARRAY,
    PRIMARY KEY (user_id)
  );

-- inserting data into array field
INSERT INTO
  users (user_id, email, phone_numbers)
VALUES
  (
    1,
    'admin@site.com',
    '{"123123897", "39847928347", "53475934875"}'::text[]
  );
```

```sql
-- alternative syntax
phone_numbers TEXT[],
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
    user_id BIGSERIAL,
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

##### Alternative approach

```sql
create table
  "user" (
    id uuid not null default gen_random_uuid (),
    email varchar not null,
    role varchar(10),
    primary key (id),
    constraint role_enum check (role in ('ADMIN', 'USER', 'EMPLOYEE')),
    constraint email_unique unique (email)
  )
```


--- 

#### Domain types
Domain types can be used to extend existing types with additional checks etc.

```sql
CREATE DOMAIN rating AS FLOAT4 CHECK (
  VALUE >= 0
  AND VALUE <= 5
);

CREATE TABLE
  book (
    book_id BIGSERIAL,
    name TEXT,
    rating rating,
    PRIMARY KEY (book_id)
  );

-- insert dummy records
INSERT INTO
  book (book_id, name, rating)
VALUES
  (1, 'Foundation', 5);
```


---

#### Composite types

```sql
CREATE TYPE address as (street TEXT, city TEXT, zip INT);

CREATE TABLE
  users (
    email VARCHAR(255) UNIQUE NOT NULL,
    address address,
    PRIMARY KEY (email)
  );

INSERT INTO users (email, address) 
VALUES ('admin@site.com', ROW('Main street', 'Lahore', 5400));
```

```sql
-- composite type fields can also be accessed as follows
INSERT INTO users (email, address.street, address.city, address.zip) 
VALUES ('admin@site.com', 'Main street', 'Lahore', 5400);
```


---

#### Pagination 

```sql
SELECT
  *
FROM
  users
LIMIT
  2
OFFSET 0;
```

**Note**: `OFFSET 0` will return the first page of results.

**Note**: The `LIMIT` keyword is supported by `MySQL`, `PostgreSQL` and `SQLite` but it may not be supported by other databases.


##### Example

```sql
SELECT *, COUNT(*) OVER() AS total_count FROM users u
WHERE u.deleted_at IS NULL
LIMIT 10
OFFSET 0;
```

**Note**: The above query will not take into account the `LIMIT` and `OFFSET` options when calculating the `total_count` value.


---

#### Relationships

##### One-to-one

**Mandatory one-to-one**: Adding relationship field to the parent entity with `UNIQUE` constraint ensures that the a child entity will always exists for the parent. Do note that this does not prevent orphan child entities. 

E.g. In the following SQL schema, all `users` will have `profiles` but it is not necessary that all `profiles` will have associated users.

```sql
-- table schema
CREATE TABLE
  profiles (
    profile_id BIGSERIAL,
    name VARCHAR(255),
    PRIMARY KEY (profile_id)
  );

CREATE TABLE
  users (
    user_id BIGSERIAL,
    email VARCHAR(255) UNIQUE NOT NULL,
    -- notice the unique constraint (1:1)
    profile_id BIGSERIAL UNIQUE NOT NULL,
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


**Optional one-to-one**: Adding relationship field to the child entity with `UNIQUE` constraint ensures that all child entities will be associated with parent entities. However, this does not mean that all parent entities will necessarily have associated child entities.

E.g. In the following SQL schema, it is ensured that all `profiles` will have associated `users`. However, it is possible that some `users` may not have associated `profile`.

```sql
CREATE TABLE
  users (
    user_id BIGSERIAL NOT NULL,
    email text UNIQUE NOT NULL,
    PRIMARY KEY (user_id)
  );

CREATE TABLE
  profiles (
    profile_id BIGSERIAL NOT NULL,
    title TEXT NOT NULL,
    -- notice the unique constraint (1:1)    
    user_id BIGSERIAL UNIQUE NOT NULL,
    PRIMARY KEY (profile_id),
    FOREIGN KEY (user_id) REFERENCES users (user_id)
  );

-- insert dummy record
WITH
  user_insert AS (
    INSERT INTO
      users (email)
    VALUES
      ('user@site.com') RETURNING user_id
  )
INSERT INTO
  profiles (profile_id, title)
VALUES
  (
    (
      SELECT
        user_id
      from
        user_insert
    ),
    'Post one title'
  );

-- fetch from parent entity
SELECT
  users.user_id,
  users.email,
  profiles.title
FROM
  users
  JOIN profiles ON users.user_id = profiles.user_id
WHERE
  users.user_id = 1;

-- fetch from child entity
SELECT
  users.user_id,
  users.email,
  profiles.title
FROM
  profiles
  JOIN users ON profiles.user_id = users.user_id
WHERE
  users.user_id = 1;
```


---

##### One-to-many

```sql
-- table schema
CREATE TABLE
  users (
    user_id BIGSERIAL,
    email VARCHAR(100),
    PRIMARY KEY (user_id)
  );

CREATE TABLE
  posts (
    post_id BIGSERIAL,
    title VARCHAR(100) UNIQUE,
    -- notice user_id has no unique constraint (1:M)
    user_id BIGSERIAL NOT NULL,
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
    role_id BIGSERIAL NOT NULL,
    role_name VARCHAR (100) NOT NULL,
    PRIMARY KEY (role_id)
  );

CREATE TABLE
  users (
    user_id BIGSERIAL NOT NULL,
    email VARCHAR (255) UNIQUE NOT NULL,
    password VARCHAR (255),
    PRIMARY KEY (user_id)
  );

CREATE TABLE
  user_roles (
    user_role_id BIGSERIAL NOT NULL,
    user_id BIGSERIAL NOT NULL,
    role_id BIGSERIAL NOT NULL,
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


---

#### Relationships and Delete cascades

When creating relationships, always question yourself which table is the `parent` and which table is the `child`. This is because we will very likely have `delete cascade` in our foreign relationships. Consider the following schema.

```sql
create table "user" (
  id uuid not null
  , email varchar(255) not null
  , password varchar(255) not null  
  , created_at timestamp not null default now()
  , updated_at timestamp not null default now()
  , primary key (id)
  , constraint email_unique unique(email)
);

create index user_email_idx on "user"(email);

create table user_profile (
  id uuid not null
  , name varchar(255)  
  , address text 
  , city varchar(255)
  , country varchar(255)  
  , user_id uuid not null
  , primary key (id)
  , foreign key (user_id) references "user"(id) on delete cascade
  , constraint user_id_unique unique(user_id)
);

create index user_profile_user_id_idx on user_profile(user_id);
```

In this schema, `user` is the parent and `user_profile` is the child table. This is an **optional one-to-one** relation because a `user` may not have any associated `user_profile`. 

Notice the `user_id` field with `delete cascade` in the `user_profile` table. This ensures that when a `user` is deleted, the associated `user_profile` is also deleted.

To sum up, is `delete cascade` is specified, the entry in child table will be deleted when the entry in the parent table is deleted.

---  
#### JSON Aggregation

We can use this trick to fetch records of relationships as JSON array. This will make it incredibly easier to serialise returned data into native language of our choosing.

```sql
CREATE TABLE
  posts (
    post_id UUID DEFAULT gen_random_uuid(),
    title TEXT NOT NULL,
    PRIMARY KEY (post_id)
  );

CREATE TABLE
  comments (
    comment_id UUID DEFAULT gen_random_uuid(),
    text VARCHAR(255) NOT NULL,
    post_id UUID NOT NULL,
    PRIMARY KEY (comment_id),
    FOREIGN KEY (post_id) REFERENCES posts (post_id)
  );
```

```sql
SELECT
  posts.post_id,
  posts.title,
  jsonb_agg (
    jsonb_build_object (
      'comment_id',
      comments.comment_id,
      'text',
      comments.text
    )
  ) as comments
FROM
  posts
  JOIN comments ON posts.post_id = comments.post_id
GROUP BY
  posts.post_id,
  posts.title;
```


##### A better implementation

```sql
create table
  users (
    user_id uuid default gen_random_uuid (),
    email text not null,
    primary key (user_id),
    constraint email_unique unique (email)
  );

create table
  posts (
    post_id uuid default gen_random_uuid (),
    title text not null,
    user_id uuid not null,
    primary key (post_id),
    foreign key (user_id) references users (user_id)
  );
```

```sql
select
  users.user_id,
  users.email,
  coalesce(
    jsonb_agg (posts) filter (where posts.user_id is not null),
    to_jsonb('[]'::text)
  ) as posts
from
  users
  left join posts on users.user_id = posts.user_id
group by
  users.user_id
```

**Note**: `coalesce` is a variadic function which returns the first non-null value it is provided. In the above example, the first argument to `coalesce` will be `NULL` when no `posts` are found against the `user`. The second argument to `coalesce` will be a non-null value, therefore it will be returned instead of `NULL`.


---

#### Transactions

##### ACID
ACID is an acronym that refers to the set of 4 key properties that define a transaction.

- **Atomicity**: Each statement in a transaction (to read, write, update or delete data) is treated as a single unit. Either the entire statement is executed, or none of it is executed. This property prevents data loss and corruption from occurring in case of system failure.

- **Consistency**: Ensures that transactions only make changes to tables in predefined, predictable ways. Transactional consistency ensures that corruption or errors in your data do not create unintended consequences for the integrity of your table.

- **Isolation**: When multiple users are reading and writing from the same table all at once, isolation of their transactions ensures that the concurrent transactions don't interfere with or affect one another. Each request can occur as though they were occurring one by one, even though they're actually occurring simultaneously.

- **Durability**: Ensures that changes to your data made by successfully executed transactions will be saved, even in the event of system failure.

```sql
-- table schema as some dummy data
CREATE TABLE
  accounts (
    account_id BIGSERIAL,
    balance BIGINT NOT NULL,
    PRIMARY KEY (account_id),
    CONSTRAINT balance_nonnegative CHECK (balance >= 0)
  );
  
INSERT INTO accounts (account_id, balance) 
VALUES (1, 100000), (2, 20000), (3, 40500000);
```

**Note**: `BIGINT` is used to store currency values in cents.

```sql
BEGIN;
UPDATE accounts SET balance = balance - 100000 WHERE account_id = 1;
UPDATE accounts SET balance = balance + 100000 WHERE account_id = 2;
COMMIT;
```


---

#### Performance optimisations

##### Prepared statements

```sql
-- define the prepared statement
PREPARE
  users_insert AS
INSERT INTO
  users (name, email)
VALUES
  ($1, $2);
```

```sql
-- execute existing prepared statement
EXECUTE users_insert ('User one', 'user_one@site.com'); 
```

**Note**: Prepared statements are scoped to connection, this means that only the session which prepares the statement can execute it.


##### Indexing

A good rule of thumb is to create database indexes for everything that is referenced in the `WHERE`, `HAVING` and `ORDER BY` parts of your SQL queries.

```sql
-- create indexes on fields frequently used for querying tables
CREATE INDEX users_index ON users (email, name);
```

```sql
-- remove index if not required
DROP INDEX users_index;
```

**Note**: Indexes help with `read` speeds. However, they slow down `write` speeds because with every new records inserted, indexes have to be updated as well.


##### Partitioning

```sql
-- create the original table: will be partitioned by day (through timestamp)
CREATE TABLE
  events (
    event_id UUID NOT NULL,
    payload JSON NOT NULL,
    source INET NOT NULL,
    event_timestamp TIMESTAMP
  )
PARTITION BY
  RANGE (event_timestamp);

-- create subpartitions for single days
CREATE TABLE
  events_20230401 PARTITION OF events FOR
VALUES
FROM
  ('2023-04-01') TO ('2023-04-02');

CREATE TABLE
  events_20230402 PARTITION OF events FOR
VALUES
FROM
  ('2023-04-02') TO ('2023-04-03');
```

Caveats

- The sub-partition tables in the above example will need to be created using a scheduler like CRON job etc.
- If a query has to multiple partitions, it will be slower than if we had not used partitioning at all.
- If a table is partitioned, it cannot have a global unique row identifier. However, row IDs can be unique within any single partition. 


---

##### Stored Procedures
Procedures are reusable blocks of statements, which don't return a value.

```sql
-- example table with some dummy data
CREATE TABLE
  accounts (
    account_id BIGSERIAL,
    balance BIGINT NOT NULL,
    PRIMARY KEY (account_id),
    CONSTRAINT balance_nonnegative CHECK (balance >= 0)
  );

INSERT INTO
  accounts (account_id, balance)
VALUES
  (1, 100),
  (2, 300),
  (3, 4000);
```

```sql
CREATE
OR
REPLACE
  PROCEDURE transfer_balance (
    from_account INTEGER,
    to_account INTEGER,
    amount BIGINT
  ) AS $$ BEGIN
  -- deduct from sender
UPDATE
  accounts
SET
  balance = balance - amount
WHERE
  account_id = from_account;

-- add to recepient
UPDATE
  accounts
SET
  balance = balance + amount
WHERE
  account_id = to_account;

COMMIT;
END;
$$ LANGUAGE plpgsql;
```

**Note**: The statements defined within the procedure body are executed as a single transaction. This means, when a procedure is called, it will either succeed entirely or fail entirely.

```
-- list out all stored procedures inside psql shell
db=# \df
```

```sql
-- execute a stored procedure
CALL transfer_balance (1, 2, 100);
```

```sql
-- drop procedure if not required
DROP PROCEDURE
  transfer_balance (
    from_account INTEGER,
    to_account INTEGER,
    amount BIGINT
  );
```


---

#### Stored functions

```sql
-- define schema
CREATE TABLE
  profiles (
    profile_id BIGSERIAL,
    name TEXT,
    address TEXT,
    PRIMARY KEY (profile_id)
  );

CREATE TABLE
  users (
    user_id BIGSERIAL,
    email TEXT UNIQUE,
    profile_id BIGSERIAL UNIQUE, -- one-to-one relation  
    PRIMARY KEY (user_id),
    FOREIGN KEY (profile_id) REFERENCES profiles (profile_id)
  );

-- insert dummy data
INSERT INTO
  profiles (profile_id, name, address)
VALUES
  (1, 'Admin', '12 Main street'),
  (2, 'Customer', '13 Street');

INSERT INTO
  users (user_id, email, profile_id)
VALUES
  (1, 'admin@site.com', 1),
  (2, 'customer@site.com', 2);
```

```sql
-- define stored functions and their return (composite) types
CREATE TYPE user_with_profile as (email TEXT, name TEXT, address TEXT);

CREATE
  FUNCTION get_user (id INT) RETURNS user_with_profile AS $$
SELECT
  users.email,
  profiles.name,
  profiles.address
FROM
  users
  JOIN profiles ON users.profile_id = profiles.profile_id
WHERE
  users.user_id = id
LIMIT
  1 $$ LANGUAGE SQL;

-- execute defined function
SELECT
  *
FROM
  get_user (1);
```

**Note**: If we are simply returning a row from an existing (single) table, we can put the name of the table as the function return type.

```sql
-- remove a defined function
DROP FUNCTION get_user (id INT);
```


---

#### Hashing passwords inside PostgreSQL

PostgreSQL hashing functions rely on `pgcrypto` extension, it needs to be manually enabled on the database.

```sql
-- enable extension on the current database
CREATE EXTENSION pgcrypto;
```

```sql
-- define a stored function for quickly hashing passwords
CREATE
OR
REPLACE
  FUNCTION hash_password (password VARCHAR(255)) RETURNS VARCHAR(255) AS $$ BEGIN
RETURN
  crypt (password, gen_salt ('bf'));

END;
$$ LANGUAGE plpgsql;
```

```sql
-- hash password at the time of record creation
INSERT INTO
  users (user_id, email, password)
VALUES
  (
    gen_random_uuid (),
    'admin@site.com',
    hash_password ('abc123123')
  );
```


---

#### Views

```sql
CREATE TABLE
  sites (
    site_id BIGSERIAL,
    site_name TEXT,
    PRIMARY KEY (site_id)
  );

CREATE TABLE
  orders (
    order_id BIGSERIAL,
    amount DECIMAL,
    PRIMARY KEY (order_id)
  );

CREATE TABLE
  site_orders (
    site_id BIGSERIAL,
    order_id BIGSERIAL,
    PRIMARY KEY (site_id, order_id),
    FOREIGN KEY (site_id) REFERENCES sites (site_id),
    FOREIGN KEY (order_id) REFERENCES orders (order_id)
  );
```

```sql
CREATE VIEW
  site_orders_view AS
SELECT
  sites.site_name,
  orders.order_id,
  orders.amount
FROM
  site_orders
  JOIN sites ON site_orders.site_id = sites.site_id
  JOIN orders on site_orders.order_id = orders.order_id
WHERE
  orders.amount > 100;
```

```sql
SELECT * FROM site_orders_view;
```


---

#### N+1 query problem
N+1 queries are a performance problem in which the application makes database queries in a loop, instead of making a single query that returns or modifies all the information at once. Each database connection takes some amount of time, so querying the database in a loop can be many times slower than doing it just once. This problem often occurs when you use an object-relational mapping (ORM) tool in web frameworks like Django or Ruby on Rails.


---

#### Optional filter parameters

```sql
SELECT * FROM people
WHERE 
	employed = TRUE
	AND ($1 IS NULL OR age > $1)
```

In the above query, `$1` is a nullable value for `age`. If we pass in a non-null value, the condition `age > $1` will apply. Is we pass in a null value, only the first portion of the condition i.e. `$1 IS NULL` will evaluate and short-circuit the condition.
