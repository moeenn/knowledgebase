```bash
$ pip3 install asyncio
```


#### Example
```python
import asyncio


async def slow_function(id: str) -> str:
    await asyncio.sleep(1)
    return f"[Done] {id}"


async def main() -> None:
    result = await slow_function("one")
    print(result)


if __name__ == "__main__":
    asyncio.run(main())
```

##### Await multiple Futures
```python
# this is effectively synchronous because all Futures are awaited in sequence
async def main() -> None:
    for i in range(10):
        result = await slow_function(i)
        print(result)
```

```python
# execute and await all at once
async def main() -> None:
    results = await asyncio.gather(*[slow_function(i) for i in range(10)])
    print(results)
```


---

#### Async generators

```python
from typing import AsyncIterable
...

# generate all results in sequence
async def generate_results(limit: int) -> AsyncIterable[str]:
    for i in range(limit):
        result = await slow_function(i)
        yield result


async def main() -> None:
    async for result in generate_results(10):
        print(result)

    # async list comprehension
    results = [result async for result in generate_results(3)]
```


---

#### Convert synchronous functions to async

```python
# sync function e.g. could be sending out requests
def slow_function_sync(id: int) -> str:
    time.sleep(0.5)
    return f"[Done] {id}"


# wrapper to convert sync function into async 
async def slow_function_async(id: int) -> str:
    return await asyncio.to_thread(slow_function_sync, id)


async def main() -> None:
    for i in range(4):
        # await as async
        result = await slow_function_async(i)
        print(result)
```
