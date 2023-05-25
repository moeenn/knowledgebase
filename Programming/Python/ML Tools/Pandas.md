```bash
$ pip3 install pandas
```


##### Basic usage
```python
import pandas as pd

# load CSV file, a URL of files can also be provided
df = pd.read_csv("./survey/survey_results_public.csv")

# get rows and columns for the data frame
df.shape

# get top rows
df.head(10) 

# get bottom rows
df.tail(5)
```


##### Configuration
```python
# by default only 20 columns will be displayed 
pd.set_option("display.max_columns", 85)

# by default, only some top and bottom rows will be displayed
pd.set_option("display.max_rows", 85)
```


---

#### Custom `dataframes`
```python
people = {
    "name": ["Mr. Admin", "Ms. Customer"],
    "role": ["Admin", "User"],
    "email": ["admin@site.com", "user@site.com"],
}

custom_df = pd.DataFrame(people)

# display columns in a dataframe
custom_df.columns

# access single column values (returned type is pandas.core.series.Series)
custom_df["email"]

# access multiple columns (returned type is pandas.core.frame.DataFrame)
custom_df[["name", "email"]]

# access first row in dataframe (access by index)
custom_df.iloc[0]

# access first two rows by index
custom_df.iloc[[0, 1]]

# access email address of first two rows, columns cannot be referenced by name (hence index 2)
custom_df.iloc[[0, 1], 2]

# access first two rows by multiple labels
custom_df.loc[[0, 1], ["email", "role"]]

# range slicing, start and end indices are inclusive
df.loc[0:1, "CareerSat":"WorkRemote"]
```


---

#### Indices
```python
people = {
    "name": ["Mr. Admin", "Ms. Customer"],
    "role": ["Admin", "User"],
    "email": ["admin@site.com", "user@site.com"],
}

custom_df = pd.DataFrame(people)

# set email column as index (temporarily)
custom_df.set_index('email')

# set email column as index (modify actual dataframe)
custom_df.set_index('email', inplace=True)

# check the current indices and their values
custom_df.index

# loc method now accepts emails and index (now numeric indices will not work)
custom_df.loc['user@site.com']

# we can still access rows using numeric indices
custom_df.iloc[0]

# reset index to default
custom_df.reset_index(inplace=True)

# setting default index column when loading CSV
df = pd.read_csv("./survey/survey_results_public.csv", index_col="Respondent")

# sort records by index value
custom_df.sort_index(ascending=True)
```


---

#### Filtering
```python
# this returns a series of True / False values which can then be applied to the dataframe 
# & means AND
# | means OR
# ~ means NOT
name_filter = (df["last"] == "Doe") & (df["first"] == "John")

# get filtered data
df[name_filter]

# get filtered data (recommended)
df.loc[name_filter]

# negate a filter i.e. get everything that doesn't match the filter
df.loc[~filt]

# finding by list of values
countries = ["United States", "India", "United Kingdom", "Germany", "Canada"]
countries_filter = df["Country"].isin(countries)

# find by checking text content
language_filter = df["LanguageWorkedWith"].str.contains("Python", na=False)
df.loc[language_filter, ["LanguageWorkedWith", "ConvertedComp"]]
```


---

##### Modifying Columns
```python
# view existing columns
df.columns

# update values for all columns
df.columns = ["First name", "Fast name", "Email", "User role"]

# using list comprehensions
df.columns = [col.lower() for col in df.columns]

# using string methods
df.columns.str.replace(" ", "_")

# rename columns
df.rename(columns={"user_role": "role", "first_name": "f_name"}, inplace=True)

# adding a new column
df["full_name"] = df["first"] + " " + df["last"]

# removing columns
df.drop(columns=["first", "last"], inplace=True)

# split existing column value into multiple new columns
df[["f_name", "l_name"]] = df["full_name"].str.split(" ", expand=True)
```

##### Modifying Rows
```python
# update all record values
df.loc[2] = ["John", "Smith", "john_smith@site.com", "ADMIN"]

# update single record value
df.loc[1, "first"] = "Alice"

# update specific record values
df.loc[2, ["last", "email"]] = ["Cane", "john_cane@site.com"]

# find and update multiple values
name_filter = (df["last"] == "Doe")
df.loc[name_filter, "last"] = "Kimchi"

# modify all column values
df["email"] = df["email"].str.lower()

# remove row by index
df.drop(index=1, inplace=True)

# find and remove records
drop_filter = (df["first"] == "Jane")
df.drop(index=df[drop_filter].index, inplace=True)
```


---

#### Apply function
```python
# working on series object (i.e. df["email"])
update_email = lambda email: email.upper()
df["email"] = df["email"].apply(update_email)

# working with dataframe object: apply method will be applied to all series in the dataframe object
df.apply(pd.Series.min)
# OR
df.apply(lambda s: s.min())
```


##### DataFrame Applymap function
```python
# apply a function to every value in every series in the dataframe, this method is only available on dataframes
df.applymap(lambda v: v.lower())
# OR
df.applymap(str.lower)
```


##### Series Map function
```python
# This method will replace all instances of "John" with "Date" 
# in column "first". 
# Values not matched will be converted to NaN. If this is not the 
# desired behavior, use replace method
df["first"] = df["first"].map({ "John": "Dale" })
```


##### Series Replace function
```python
# only matched values will be changes, unmatched values will not be modified
df["first"] = df["first"].replace({ "John": "Dale" })
```


---

#### Sorting
```python
# sort by single column (rows will retain their original indices)
df.sort_values(by="last", ascending=True)

# sort descending by "last" column, then sort ascending by "first" column
df.sort_values(by=["last", "first"], ascending=[False, True], inplace=True)

# sort using index
df.sort_index(inplace=True)

# sort series object
df["email"].sort_values(ascending=False)

# get the largest column values
df["ConvertedComp"].nlargest(10)

# get full details of records sorted by provided column
df.nlargest(10, "ConvertedComp")

# get the smallest values
df["ConvertedComp"].nsmallest(10)
df.nsmallest(10, "ConvertedComp")
```


---

#### Aggregate Functions
Note: Mean value is too heavily affected by the outliers. Generally we should use median value as it is a better representative of the data

```python
# get median for a single column
df["ConvertedComp"].median()

# get general stats about the dataframe
df.describe()

# get all unique values in column
df["YearsCode"].unique()

# get number of occurrences for each response value
df["Hobbyist"].value_counts()

# get percentage of occurrence of each response value
df["SocialMedia"].value_counts(normalize=True)

# show top social for each country group
country_group["SocialMedia"].value_counts() # .head(50)

# show top social media by specific country
country_group["SocialMedia"].value_counts().loc["India"]

# get median value for each country group
country_group["ConvertedComp"].median() # .loc["Germany"]

# run multiple aggregate functions
country_group["ConvertedComp"].agg(["median", "mean"])
```

```python
# percentage of people from each country that know python
country_resp = df["Country"].value_counts()
knows_python = country_group["LanguageWorkedWith"].apply(lambda g: g.str.contains("Python").sum())

python_df = pd.concat([country_resp, knows_python], axis="columns")
python_df.rename(columns={"count": "NonRespondents", "LanguageWorkedWith": "NumKnowsPython"}, inplace=True)

python_df["pctKnowsPython"] = (python_df["NumKnowsPython"] / python_df["NonRespondents"]) * 100
python_df.sort_values(by="pctKnowsPython", ascending=False, inplace=True)
```


---

#### Cleaning Date
```python
import numpy as np

people = {
    "first": ["Corey", "Jane", "John", "Adam", np.nan, None, "NA"],
    "last": ["Schafer", "Doe", "Doe", "Doe", "Schafer", np.nan, "Missing"],
    "email": ["CoreyMSchafer@gmail.com", "JaneDoe@email.com", "JohnDoe@email.com", None, np.nan, "anon@site.com", "NA"],
    "age": ["33", "55", "63", "36", None, None, "Missing"],
}

df = pd.DataFrame(people)

# check which rows and columns contain NA values
df.isna()

# remove unclean data
for item in ["NA", "Missing"]: 
    df.replace(item, np.nan, inplace=True)

# remove all missing values
df.dropna()

# remove NA values when reading a csv
na_values = ["NA", "Missing"]
df = pd.read_csv("./path/to/data.csv", index_col="Respondent", na_values=na_values)

# the default args for the above method are as follows
# index simply means rows. Alternatively it can be "columns" which will drop any columns that 
# don't have any values
# any means a row will be dropped if it has any missing values. Alternatively, it can be "all"
df.dropna(axis="index", how="any")

# drop row if values are missing in provided columns
df.dropna(axis="index", how="any", subset=["last", "email"], inplace=True)

# provide default value for all NA fields
df.fillna("MISSING")

# cast column values to specific data types. If the column has NA values then casting to int will fail
# because np.nan is of type float and all values in column must be of same data type
df["age"] = df["age"].astype(float)
```


---

#### Time series data
```python
# parse a single string as Timestamp object, format is optional
pd.to_datetime(df.loc[0, "Date"], format="%Y-%m-%d %I-%p")

# parse all values in column as Timestamp
df["Date"] = pd.to_datetime(df["Date"], format="%Y-%m-%d %I-%p")

# parse columns as Timestamps while loading CSV
df = pd.read_csv("date.csv", parse_dates=["Date"], date_format="%Y-%m-%d %I-%p")

# get day name for a specific date
df.loc[0, "Date"].day_name()

# get day name for all values in column
df["Date"].dt.day_name()

# get earliest date in date column
df["Date"].min()

# get latest gate in date column
df["Date"].max()

# get timestamp delta
df["Date"].max() - df["Date"].min()

# filter data type time range
date_filter = (df["Date"] >= pd.to_datetime("2019-1-1")) & (df["Date"] < pd.to_datetime("2020-1-1"))
df.loc[date_filter]

# if date column is set as index, we can also access data for a year as follows
df.loc["2019"]

# data for a time range can also be filtered using slices
df.loc["2019-01":"2019-02"]

# get highest value for specific day
df.loc["2020-01-01", "High"].max()

# get highest values for all days
# resample args: Link
highs = df["High"].resample("D").max()

# Tip: quickly plot inside jupyter notebooks
%matplotlib inline
highs.plot()

# apply different aggregation functions to different columns
df.resample("W").agg({ "Close": "mean", "High": "max", "Low": "min", "Volume": "sum" })
```


---

#### Writing output files - CSV / TSV
```python
# generate CSV file from dataframe
custom_df.to_csv("survey/modified.csv")

# generate TSV (tab separated values) from dataframe
custom_df.to_csv("survey/modified.tsv", sep="\t")
```


---

#### Working with Excel files
```bash
$ pip3 install xlwt openpyxl xlrd
```

```python
# reading in excel files
xl_df = pd.read_excel("survey/modified.xlsx", index_col="Respondent")

# writing to excel file
custom_df.to_excel("survey/modified.xlsx")
```


---

#### Working with JSON files
```python
# reading a json file
df = pd.read_json("survey/modified.json", orient="records", lines=True)

# writing to json file
custom_df.to_json("survey/modified.json", orient="records", lines=True)
```


---

#### Working with SQL Databases
```bash
$ pip3 install SQLAlchemy psycopg2-binary
```

```python
# establish connection
engine = create_engine("postgresql://devuser:devpass@localhost:5432/sample")

# read data directly from database (full table)
sql_df = pd.read_sql("custom_table_name", engine, index_col="Respondent")

# read results of sql query as dataframe
query = "SELECT * FROM custom_table_name"
sql_df = pd.read_sql_query(query, engine, index_col="Respondent")

# write directly to database, new table will be created
custom_df.to_sql("table_name", engine)

# write directly to database, table must exist and data will be overwritten
custom_df.to_sql("custom_table_name", engine, if_exists="replace")
```