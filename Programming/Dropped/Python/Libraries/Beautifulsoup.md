```bash
# installation
$ pip3 install beautifulsoup4 lxml requests
```


#### Basic example
```python
from bs4 import BeautifulSoup
import requests

webpage = "example.html"

with open(webpage, "rt") as html_file:
	soup = BeautifulSoup(html_file, "lxml")
	print(soup.prettify())
```

