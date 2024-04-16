```bash
$ pip3 install pydantic email-validator 
```

```python
from pydantic import BaseModel, EmailStr, UUID4, Field, ValidationError
import datetime
from datetime import datetime
from enum import Enum
from uuid import uuid4


class PostType(Enum):
    Blog = "BLOG"
    Technical = "TECHNICAL"


class Post(BaseModel):
    id: UUID4
    title: str
    content: str
    publish_date: datetime | None
    type: PostType


class User(BaseModel):
    id: UUID4
    email: EmailStr
    password: str = Field(min_length=8)
    approved: bool
    posts: list[Post]


def main() -> None:
    raw: dict = {
        "id": uuid4(),
        "email": "admin@site.com",
        "password": "123_Apple",
        "approved": True,
        "posts": [
            {
                "id": uuid4(),
                "publish_date": "2022-10-01 10:30",
                "title": "Lorem",
                "content": "ipsum",
                "type": "BLOG",
            }
        ]
    }

    try:
	    # throws if data is not valid
        user = User(**raw)
        print("valid user", user)
    except ValidationError as e:
        print("error", e.json())


if __name__ == "__main__":
    main()
```
