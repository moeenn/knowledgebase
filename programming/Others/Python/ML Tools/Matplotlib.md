```bash
$ pip3 install matplotlib
```


##### Usage with `Jupyter` notebook
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

#### Applying fill betweens

```python
import pandas as pd
from matplotlib import pyplot as plt

data = pd.read_csv("data.csv")

ages = data["Age"]
salaries_all = data["All_Devs"]
salaries_python = data["Python"]
salaries_js = data["JavaScript"]

plt.plot(ages, salaries_all, label="All Developers")
plt.plot(ages, salaries_python, label="Python developers")

plt.fill_between(
    ages,
    salaries_python,
    salaries_all,
    where=(salaries_python > salaries_all),
    interpolate=True,
    alpha=0.25,
    label="Above Avg."
)

plt.fill_between(
    ages,
    salaries_python,
    salaries_all,
    where=(salaries_python <= salaries_all),
    interpolate=True,
    color="red",
    alpha=0.25,
    label="Below Avg."
)

plt.title("Median developer salaries by Age")
plt.xlabel("Age")
plt.ylabel("Median salary")

plt.legend(loc="lower right")
plt.grid(True)
plt.show()
```

**Note**: In this example we are applying fill between the two plot lines. However, we can also apply fill between line and a fixed y-position. 

```python
median = 55000

plt.fill_between(
    ages,
    salaries_python,
    median,
    where=(salaries_python > median),
    interpolate=True,
    alpha=0.25,
    label="Above median"
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


---

#### Stack plots

```python
from matplotlib import pyplot as plt

minutes = [i for i in range(1, 10)]
scores = {
    "player_one": [1, 2, 3, 3, 4, 4, 4, 4, 5],
    "player_two": [1, 1, 1, 1, 2, 2, 2, 3, 4],
    "player_thr": [1, 1, 1, 2, 2, 2, 3, 3, 3],
}

labels = ["Player One", "Player Two", "Player Three"]

plt.stackplot(minutes, scores["player_one"], scores["player_two"], scores["player_thr"], labels=labels)

plt.title("Player scores")
plt.xlabel("Minutes")
plt.ylabel("Scores")
plt.legend(loc="upper left")

plt.show()
```


---

#### Histograms
Data is grouped together in bins. Bins are displayed as vertical bars. In the following example a histogram is better than a bar plot because drawing ~100 bars would be very confusing.

```python
from matplotlib import pyplot as plt

ages = [18, 19, 21, 25, 26, 26, 30, 32, 38, 45, 55]
bins = [20, 30, 40, 50, 60]

plt.hist(ages, bins=bins, edgecolor="black")
plt.grid(True)
plt.show()
```

**Note**: The data includes ages between 10-20, but we haven't defined a bin for it. Ages in this range will be excluded from the histogram.


---

#### Scatter plots
Scatter plots are very useful in visualizing correlations and outliers.

```python
from matplotlib import pyplot as plt

plt.style.use("ggplot")

x = [5, 7, 8, 5, 6, 7, 9, 2, 3, 4, 4, 4, 2, 6, 3, 6, 8, 6, 4, 1]
y = [7, 4, 3, 9, 1, 3, 2, 5, 2, 4, 8, 7, 1, 6, 4, 9, 7, 7, 5, 1]
colors = [7, 5, 9, 7, 5, 7, 2, 5, 3, 7, 1, 2, 8, 1, 9, 2, 5, 6, 7, 5]

plt.scatter(x, y, s=50, c=colors, cmap="Greens")

cbar = plt.colorbar()
cbar.set_label("Satisfaction")

plt.grid(True)
plt.show()
```


---

#### Time series data
```python
from datetime import datetime
import pandas as pd

plt.style.use("ggplot")

dates = [
    datetime(2019, 5, 24),
    datetime(2019, 5, 25),
    datetime(2019, 5, 26),
    datetime(2019, 5, 27),
    datetime(2019, 5, 28),
    datetime(2019, 5, 29),
    datetime(2019, 5, 30)
]

y = [0, 1, 3, 4, 6, 5, 7]

plt.plot_date(dates, y, linestyle="solid")
plt.show()
```

Note: When reading dates from CSV files, they will not be automatically converted to `Datetime` objects. We can do it manually as follows.

```python
data = pd.read_csv("data.csv")
data["date"] = pd.to_datetime(data["date"])
data.sort("date", inplace=True)
```


---

#### Live plots

```python
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import pandas as pd
from itertools import count
import random

plt.style.use("ggplot")

x_vals = []
y_vals = []

index = count()

def animate(i):
    x_vals.append(next(index))
    y_vals.append(random.randint(0, 5))

    # clean previous lines and draw new one
    plt.cla()
    plt.plot(x_vals, y_vals)


fig = plt.gcf()
anim = FuncAnimation(fig, animate, interval=2000)

plt.plot(x_vals, y_vals)
plt.show()
```


---

#### Subplots

```python
import matplotlib.pyplot as plt
import pandas as pd

plt.style.use("ggplot")

data = pd.read_csv("data.csv")
age = data["Age"]
all_devs = data["All_Devs"]
js_devs = data["JavaScript"]
py_devs = data["Python"]


fig, (axis_one, axis_two) = plt.subplots(nrows=2, ncols=1, sharex=True)

axis_one.plot(age, all_devs, linestyle="--", label="All Developers")
axis_one.set_title("All developers")
axis_one.set_ylabel("Median salary")
axis_one.legend()

axis_two.plot(age, js_devs, label="JS")
axis_two.plot(age, py_devs, label="Python")
axis_two.set_xlabel("Age")
axis_two.set_ylabel("Median salary")
axis_two.legend()

plt.show()
```