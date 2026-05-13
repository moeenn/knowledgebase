
Types of machine learning

- Supervised learning: Correct labels are provided with data
- Unsupervised learning: Labels are not provided, data is grouped automatically
- Reinforced learning: System is provided reward or penalty based on its actions. The objective is to maximize the reward.


```bash
# installation
$ pip3 install scikit-learn
```


---

#### Loading data

**Features**: These are attributes, independent variables used as input. They are denoted by `X`. They will be numbers between `-1` and `+1`. Think of each of the features as a dimension on a matrix i.e. 3 features means a 3D-matrix.

**Label**: These are dependent on the input features. They are denoted by `y`.

```python
from sklearn.datasets import load_iris

X, y = load_iris(return_X_y=True)

print("X", X.shape)
print("y", y.shape)

# X (150, 4)
# y (150,)
```

The `load_iris` function returns values as `numpy` arrays. The dataset (i.e. `X`) contains 150 entries with 4 features. The labels (i.e. `y`) is a single dimension array.

We don't use the entire dataset during training, because we need a different set of training and validating the results of the trained model. For this reason we can split the dataset 80-20 i.e. use 80% of the data for training and the remaining 20% for validation. 

```python
from sklearn.model_selection import train_test_split

X, y = load_iris(return_X_y=True)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2)
```

**Note**: If we use too little data for validation, the model results will not be properly validated.


---

#### K-Nearest neighbors (KNN)
KNN is a classification algorithm. Based on `k` number of closest points it determines how to classify each point.

