```bash
$ pip3 install requests
```


#### Simple GET request
```python
import requests


# download and save file at provided location
def download_file(url: str, location: str) -> None:
    res = requests.get(url, stream=True, timeout=10)
    if res.ok:
        with open(location, "wb") as file:
            file.write(res.content)


def main() -> None:
    url: str = "https://sample.site/sample.jpg"
    download_file(url, "./sample.jpg")
```


##### Useful attributes
| Attribute | Explanation | 
| -------: | :------ |   
| `response.text` | Text content of the response e.g. web pages etc. | 
| `response.content` | Binary content of the response. Return type is Byte e.g. images, documents etc. | 
| `response.status_code` | HTTP status code. Return type is Integer. e.g. 200, 404 etc. | 
| `response.ok` | Status other than client (400-) or server (500-) status codes i.e. if status code is in 400-600 range the returned value will be `False` | 
| `response.headers` | Headers of Response. Return type is a dictionary | 
| `response.url` | URL to which request was sent |  


##### Parameters to URLs
Dynamic websites often use URL parameters to serve up specific content. These parameters look like this

```
https://site.com/get?page=1&mode=public
```

When making requests we could manually change our request URL to include these requests but this could be prone to errors. The module does provide us a way to programmatically add URL parameters using dictionaries

```python
import requests


def main() -> None:
    url: str = "https://httpbin.org/get"
    params: dict[str, int] = {
        "page": 2,
        "count": 25
    }

    res = requests.get(url, params=params, timeout=10)
    if res.ok:
        print(res.url, res.json())
```


---

#### POST request
```python
import requests


def main() -> None:
    url: str = "https://httpbin.org/post"
    data: dict[str, int] = {
        "page": 2,
        "count": 25
    }

    res = requests.post(url, data=data, timeout=10)
    if res.ok:
        print(res.url, res.json())
```

The above code has been used to submit HTML forms. We will, however, need to check the HTML source to see the exact field names.


---

#### Basic Authentication
Some old websites use a method of authentication called Basic Authentication. 

```python
import requests


def main() -> None:
    # username = moeenn
    # password = testing
    url: str = "https://httpbin.org/basic-auth/moeenn/testing"

    res = requests.get(url, auth=("moeenn", "testing"), timeout=10)
    if res.ok:
        print(res.text)
```

**Note**: The credentials are passed as a tuple and HTTP method is GET. In case we pass incorrect credentials our test server doesn’t return any response body but the HTTP status code is 401 - Unauthorized Error.

