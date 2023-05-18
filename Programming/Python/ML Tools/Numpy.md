```bash
$ pip3 install numpy
```


#### Common Attributes
```python
import numpy as np

oned_array = np.array([1, 2, 3, 4, 5])

# specify data type
int_array = np.array([1.0, 2.4, 3.5, 4.6, 5.7], dtype=np.int64)
print(int_array)

# shape i.e. tuple of numbers: rows x cols x n
print(oned_array.shape)

# automatically inferred elements datatype
print(oned_array.dtype)

# number of dimensions in the array
print(oned_array.ndim)

# size of each element in bytes, i.e. int64 -> 8 bytes
print(oned_array.itemsize)

# access element at index, same as native python
# values in array can also be updated this way (i.e. using subscripts)
print(oned_array[2])

# convert numpy array into list
list(oned_array)

# create a copy
b = oned_array.copy()
```


---

#### Array operations
```python
a = np.array([1, 2, 3])
b = np.array([2, 0, 2])

# array addition, sum corresponding array elements, shape is still (3,)
print(a + np.array([4]))

# following is the same as the above line
c = a + np.array([4, 4, 4])
print(c)

# multiply all elements in array with one value i.e. 4
print(a * np.array([4]))
print(a * np.array([4, 4, 4]))
print(a * 4)

# produce a new array with square root function applied to all elements
print(np.sqrt(a))

# produce new array with the log of all elements
print(np.log(a))

# sum all elements in the array
np.sum()
```


---

#### Array Dot Product
```python
# method one
l1 = [4, 9, 16, 25]
l2 = [10, 20, 30, 40]


def list_dot_product(l1: list[int], l2: list[int]) -> int:
    dot = 0
    for i, _ in enumerate(l1):
        dot += l1[i] * l2[i]

    return dot


print(list_dot_product(l1, l2))
```

```python
# method two (recommended)
one = np.array(l1)
two = np.array(l2)
print(np.dot(one, two))
```

```python
# method three
a = np.array([4, 9, 16, 25])
b = np.array([10, 20, 30, 40])

# multiply all array corresponding elements
arr_mult = a * b

# generate dot product
print(np.sum(arr_mult))
```

```python
# method four
a = np.array([4, 9, 16, 25])
b = np.array([10, 20, 30, 40])

dot = a @ b
print(dot)
```


---

#### Multi-dimensional (ND) Arrays i.e. Matrices

```python
nd_array = np.array([
    [1, 2, 3, 4],
    [10, 20, 30, 40]
])

# get shape, i.e. (2, 4)
print(nd_array.shape)

# access single element i.e. 4
print(nd_array[0][3])

# same as above but more succinct
print(nd_array[0, 3])

# transpose matrix i.e. convert rows into cols and cols into rows
print(nd_array.T)

# get inverse of matrix
square_matrix = np.array([[1, 2], [3, 4]])
inv = np.linalg.inv(square_matrix)
print(inv)

# get determinant of the matrix
determinant = np.linalg.det(square_matrix)
print(determinant)

# get diagonal matrix i.e. [1, 4]
diag = np.diag(square_matrix)
print(diag)

# diagonal matrix of a one-d array is as follows
# [1, 0]
# [0, 4]
print(np.diag(diag))
```


---

#### Array slicing
```python
a = np.array([
    [1, 2, 3, 4, 5],
    [6, 7, 8, 9, 10]
])

# get first full row
print(a[0])
# same as above, slice means include all elements
print(a[0, :])

# get the last row
print(a[-1])

# get element index 3 and 4 in second row (end index non-inclusive)
print(a[1, 2:4])

# get all values in second column i.e. [2, 7]
print(a[:, 1])
```


---

#### Array conditions
```python
a = np.array([
    [1, 2, 3, 4, 5],
    [6, 7, 8, 9, 10]
])

print(a.shape)

# apply and return a new array with the same size as the original array,
# containing boolean values for whether the condition was true or not
bool_array = a > 3
print(bool_array)

# get elements which specify the above condition (as 1d array)
print(a[bool_array])

# do the same operation in one step
print(a[a > 3])

# get elements which specify a condition, while retaining the shape of the
# original matrix
# -1 will be put in place of the elements which don't satisfy our condition
b = np.where(a > 3, a, -1)
print(b)
```


---

#### Fancy Indexing
```python
a = np.array([10, 19, 30, 41, 50, 69])
b = [2, 5]

# get elements at index 2 and 5 i.e. [30, 69]
print(a[b])

# get index of elements where the condition is specified
even = np.argwhere(a % 2 == 0).flatten()
# next print the values of elements at those indices
print(a[even])
```


---

#### Change shape
```python
# shape of (6,)
a = np.array([i for i in range(1,7)])
# Or
b = np.arange(1, 7)

# change shape, the new size must fit all array elements, otherwise it will throw
c = a.reshape((2, 3))
print(c)

# adding a new axis, new shape is now (1, 6), i.e. new row added
d = a[np.newaxis, :]
print(d.shape)

# add axis, shape is now (6, 1)
e = a[:, np.newaxis]
print(e)
```


---

#### Concatenation
```python
a = np.array([[1,2], [3,4]])
b = np.array([[5,6]])

# new shape is (3, 2)
c = np.concatenate((a, b), axis=0)
print(c.shape)

# combine all elements into a 1d array, shape is (6,)
d = np.concatenate((a, b), axis=None)
print(d.shape)

# add second matrix as cols
# [[1 2 5]
# [3 4 6]]
e = np.concatenate((a, b.T), axis=1)
print(e)
```


---

#### Stacking
```python
a = np.array([1,2,3,4])
b = np.array([5,6,7,8])

# stack horizontally, shape is (8,)
c = np.hstack((a, b))
print(c)

# stack vertically, shape is (2,4)
d = np.vstack((a, b))
print(d.shape)
```


---

#### Broadcasting
```python
a = np.array([[1,2,3], [4,5,6], [7,8,9]])

b = np.array([1,0,1])
c = a + b

d = np.array([[1,0,1], [1,0,1], [1,0,1]])
# Although shape of b and d is different, e will be the same as c 
# [[ 2  2  4]
# [ 5  5  7]
# [ 8  8 10]]
e = a + d
```


---

#### Axis
```python
a = np.array([[7,8,9,10,11,12,13], [17,18,19,20,21,22,23]])

# axis
# 0 -> along columns
# 1 -> along rows
# None -> all rows and columns

# sum all values, single value is returned
print(a.sum(axis=None))

# sum along columns, returned array has shape (7,)
print(a.sum(axis=0))

# sum along row, returns array has shape (2,)
print(a.sum(axis=1))
```


---

#### Common calculations
```python
a = np.array([[7,8,9,10,11,12,13], [17,18,19,20,21,22,23]])

# sum all values, single value is returned
mean = a.mean(axis=None)
print(mean)

# variance
variance = a.var(axis=None)
print(variance)

# standard deviation
std_deviation = a.std(axis=None)
print(std_deviation)
```


---

#### Filling values
```python
# array of provided size will all values equal to zero
a = np.zeros((3, 4))
print(a)

# array of provided size will all values equal to 1
b = np.ones((2, 4))
print(b)

# array of provided size will all values equal to the provided value
c = np.full((3,5), 2.5)
print(c)

# generate identity matrix of provided with num rows and cols equal to provided value
# shape will be (5, 5)
d = np.eye(5)
print(d)
```


---

#### Random
```python
# generate random numbers in uniform distribution i.e. [0..1]
a = np.random.random((2, 4))
print(a)

# generate numbers in normal / gaussian distribution
# mean ~0
# variance ~1
b = np.random.randn(2, 4)
print(b)

# generate random ints in range (high is non-inclusive)
c = np.random.randint(low=10, high=100, size=(2, 4))
print(c)

# generate array of values picked randomly from provided options
possible_values = [10, 20, 40]
d = np.random.choice(possible_values, size=10)
print(d)
```


---

#### Eigenvalues and Eigenvectors
```python
a = np.array([[1,2], [3,4]])
eigenvalues, eigenvectors = np.linalg.eig(a)
```


---

#### Solving linear systems

**Question**: Admisssion fee at a fair is $1.50 for children and $4.00 for adults. On a certain day 2,200 people entered the fair and $5,050 is collected. How many children and how many adults attended. 

$$
x_{1} + x_{2} = 2200
$$
$$ 1.5x_{1}+4.0x_{2}=5050 $$
$$
x = 
\begin{bmatrix}
	x_{1} \\
	x_{2}
\end{bmatrix},

A = 
\begin{bmatrix}
	1 & 1 \\
	1.5 & 4.0
\end{bmatrix},

b = 
\begin{bmatrix}
	2200 \\
	5050
\end{bmatrix}
$$
$$
{Ax = b}
\Leftrightarrow
{x = A^{-1}\cdot b}
$$

```python
A = np.array([[1, 1], [1.5, 4.0]])
b = np.array([2200, 5050])

x = np.linalg.solve(A, b)
print(x) # [1500, 700]
```

