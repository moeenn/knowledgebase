```bash
$ pip3 install matplotlib
```


##### Usage with Jupyter notebook
```python
from matplotlib import pyplot as plt

# enable showing the plots inside the jupyter document
# don't use outside jupyter notebook
%matplotlib inline

# x-axis: ages
dev_x = [25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35]

# y-axis: median salaries
dev_y = [38496, 42000, 46752, 49320, 53200,
         56000, 62316, 64928, 67317, 68748, 73752]


plt.title("Developer median salaries")
plt.xlabel("Developer Age")
plt.ylabel("Median salary")
plt.plot(dev_x, dev_y)
```

**Note**: When using with an editor, we will also need `plt.show()` to actually display the plot.


---

#### Graphing multiple lines
```python
developers = {
    "age": [25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35],
    "median_salary": [38496, 42000, 46752, 49320, 53200, 56000,
                      62316, 64928, 67317, 68748, 73752],
    "py_median_salary": [45372, 48876, 53850, 57287, 63016, 65998,
                         70003, 70000, 71496, 75370, 83640]
}

plt.plot(developers["age"], developers["median_salary"], label="All devs")
plt.plot(developers["age"], developers["py_median_salary"], label="Python dev")

plt.title("Developer median salaries")
plt.xlabel("Developer Age")
plt.ylabel("Median salary")

# explicitly include the legend in the output
plt.legend()

# explicitly draw a grid
plt.grid(True)

# save as image to disk
plt.savefig("figure.png")

# open preview
plt.show()
```

Styling the lines can also be achieved as follows

```python
plt.plot(
    developers["age"],
    developers["median_salary"],
    label="All devs",
    linestyle="--",
)

plt.plot(
    developers["age"],
    developers["py_median_salary"],
    label="Python dev"
)
```


---

#### Applying in-built styles

```python
# get list of available styles
print(plt.style.available)

# apply a style to the plot (place before all code)
plt.style.use("ggplot")
```


---

#### Bar charts
The following code will generate a vertical bar-chart with multiple (3) bars. 

```python
import numpy as np
from matplotlib import pyplot as plt

plt.style.use("ggplot")

developers = {
    "age": [25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35],
    "median_salary": [38496, 42000, 46752, 49320, 53200, 
    56000, 62316, 64928, 67317, 68748, 73752],
    "py_median_salary": [45372, 48876, 53850, 57287, 63016, 
    65998, 70003, 70000, 71496, 75370, 83640],
    "js_median_salary": [37810, 43515, 46823, 49293, 53437, 
    56373, 62375, 66674, 68745, 68746, 74583]
}

x_indices = np.arange(len(developers["age"]))
bar_width = 0.25

plt.bar(
    x_indices,
    developers["median_salary"],
    label="All devs",
    width=bar_width,
)

# by default, all bars are overlayed. Here we are shifting one the of the bars
# to the right
plt.bar(
    x_indices + bar_width,
    developers["py_median_salary"],
    label="Python dev",
    width=bar_width,
)

# shift bars to the left
plt.bar(
  x_indices - bar_width,
  developers["js_median_salary"],
  label="JS dev",
  width=bar_width,
)

plt.title("Developer median salaries")
plt.xlabel("Developer Age")
plt.ylabel("Median salary")

# above, we are using the np arange to plot the x-axis, here we are overwriting 
# the labels to developer ages
plt.xticks(ticks=x_indices, labels=developers["age"])

# explicitly include the legend in the output
plt.legend()
plt.grid(True)

plt.show()
```

**Note**: If we need to draw a horizontal bar chart, we can use `plt.barh` method instead of `plt.bar`.

