SQLite3 is a standard library that comes pre-installed with python. We can use it for small to medium sized applications. The first step is to establish a connection with a db. We can connect to a db by using the `connect()` method. 

```python
import sqlite3

# using file as a db
conn = sqlite3.connect('employee.db')

# using in-memory db
conn = sqlite3.connect(':memory:')
```

After a connection has been established with a db, the next step is to create a cursor object. This object will allow us to execute SQL queries. Cursor can be created using cursor() method with the connection and queries can be executed using the execute() method on the cursor.

```python
import sqlite3

# establish connection
conn = sqlite3.connect('employee.db')

# create the cursor
cursor = conn.cursor()

# execute a query
cursor.execute("""CREATE TABLE employees (
    first TEXT,
    last TEXT,
    pay INT
)""")

# write changes to the db
conn.commit()

# close the connection to the db
conn.close()
```


##### Writing data into the table
The standard SQL query can be used to write data into a table. After the connection has been established with the db and a cursor has been created, we can do the following 

```python
cursor.execute("INSERT INTO employees VALUES('Muhammad', 'Moeen', 30000)")
```


##### Fetching data from the db
```python
# write data into the table
cursor.execute("INSERT INTO employees VALUES('Mr', 'Admin', 30000)")
cursor.execute("INSERT INTO employees VALUES('Ms', 'User', 50000)")

# get the data from the db
cursor.execute("SELECT * FROM employees WHERE first='Mr'")
user = cursor.fetchone() 
print(user)

# ('Mr', 'Admin', 30000)
```

- `fetchone()`: This will get one result a time and return it as a tuple. It will hold state and the next time we execute the same command it will return the next result. After all the results have been fetched, the method will return `None`.

- `fetchmany()`: This will get the number of results that we specify as an argument, as a list of tuples

- `fetchall()`: This will get all the results as a list of tuples. This method doesn’t take any arguments.


#### Using placeholders and tuple
```python
# write data into the table
cursor.execute("INSERT INTO employees VALUES (?, ?, ?)", (emp1.first, emp1.last, emp1.pay))
conn.commit()

conn.commit()
```

##### Using placeholders and dictionary (recommended)

```python
# write data into the table
emp1 = { 
    'first': emp1.first,
    'last': emp1.last,
    'pay': emp1.pay
    }

cursor.execute("INSERT INTO employees VALUES (:first, :last, :pay)", emp)

conn.commit()
```