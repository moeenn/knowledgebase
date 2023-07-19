
##### Databases
```sql
-- create an new database
CREATE DATABASE sample;

-- delete a database
DROP DATABASE sample;
```


---

##### Tables
```sql
-- create a new table within a database
CREATE TABLE
  users (
    id BIGSERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    email VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    location POINT NOT NULL
  );
```

`UUID` can be used as Primary key as follows.

```sql
CREATE TABLE
  users (
    id UUID DEFAULT gen_random_uuid(),
    name VARCHAR(100) NOT NULL,
    active BOOL DEFAULT (TRUE),
    PRIMARY KEY (id)
  );
```


##### Delete all tables
```sql
DROP SCHEMA public CASCADE;
CREATE SCHEMA public;
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

#### Insert Data into Table
```sql
-- insert records into table
INSERT INTO
  users (name, email, password, dob)
VALUES
  ('User one', 'user_one@site.com', 'q1w2e3r4', DATE '1990-02-10', POINT '(30.44, 50.23)'),
  ('User two', 'user_two@site.com', 'zascdvf', DATE '1998-09-17', POINT '(30.44, 50.23)');
```


---

#### Drop all tables

```sql
DROP SCHEMA public CASCADE;
CREATE SCHEMA public;
```