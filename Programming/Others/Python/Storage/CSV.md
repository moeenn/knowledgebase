CSV stands for comma separated values.  CSV files can be opened the same way as any other type of file using context managers. We will need to load up the csv file into an object before we can perform more interesting operations on it. We can do this by using the `reader()` method.

```python
import csv

with open('contacts.csv', 'rt') as csv_file:
    f_reader = csv.reader(csv_file)
    for line in f_reader:
        print(line)
```

**Note**: Freader (or whatever else you want to call it) is an object. It doesn’t hold the entire csv file in memory. It behaves pretty much like a `generator`.

In the example above, each line will be read as a list. This means that we can filter out the fields using their index values.

```python
for line in f_reader:
    # print out second, third and fourth field
    print(line[1], line[2], line[3])	
```

```python
with open('contacts.csv', 'rt') as csv_file:
    f_reader = csv.reader(csv_file)

    with open('new_file.csv', 'wt') as new_file:
        f_writer = csv.writer(new_file, delimiter='\t')

        for line in f_reader:
            f_writer.writerow(line)
```

```python
with open('contacts.csv', 'wt') as csv_file:
    field_names = ['Number', 'Multiplier', 'Result']
    csv_writer = csv.DictWriter(csv_file, fieldnames=field_names, delimiter='\t')

    # by default header will not be printed by DictWriter()
    csv_writer.writeheader()

    num = 5

    for i in range( 1, 1001 ):
        row = { field_names[0]:num, 
                field_names[1]:i, 
                field_names[2]:num*i 
              }

        csv_writer.writerow(row)
```

