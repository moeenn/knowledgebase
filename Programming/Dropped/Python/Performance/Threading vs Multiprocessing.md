- Threading is meant to reduce time of execution for IO-bound operations
- Multiprocessing is meant to reduce time of execution for CPU-bound operations 


#### Concurrency with Threading

CPU Bound vs. IO Bound operations
CPU Bound operations are compute-intensive operations that take up some time. IO Bound operations are operations that await input or output and therefore require time. Threading helps with IO Bound operations. Conversely, thread slows down CPU Bound operations.

Threading doesn’t actually run the code in parallel. When the CPU is idle (i.e. awaiting IO) the program will move on to the next instructions. This is called Asynchronous Programming.


---

#### Basic program
```python
import time
import threading
from typing import Callable


def time_execution(callback: Callable) -> Callable:
    def wrapper() -> None:
        start = time.perf_counter()
        callback()
        end = time.perf_counter()
        elapsed = round(end - start, 2)
        print(f"Time Elapsed: {elapsed}s")

    return wrapper


def slow_function(duration: float) -> None:
    print(f"Waiting {duration}s ...", end="\t")
    time.sleep(duration)
    print("[DONE]")


@time_execution
def main() -> None:
    slow_function(0.5)
    slow_function(0.5)
```


---

#### Manual Threading (not recommended)
We can implement threads in the code to make our `slow_function` function run asynchronously.

```python
import time
import threading
from typing import Callable


def time_execution(callback: Callable) -> Callable:
    def wrapper() -> None:
        start = time.perf_counter()
        callback()
        end = time.perf_counter()
        elapsed = round(end - start, 2)
        print(f"Time Elapsed: {elapsed}s")

    return wrapper



# some slow IO-bound operation
def slow_function(duration: float = 0.5) -> None:
    print(f"Waiting {duration}s ...", end="\t")
    time.sleep(duration)
    print("[DONE]")


@time_execution
def main() -> None:
    thread_one = threading.Thread(target=slow_function, args=(1.0,))
    thread_two = threading.Thread(target=slow_function)

    # start execution of each thread
    thread_one.start()
    thread_two.start()

    # ensure completion of each thread before moving on; ensure you only join
    # after all threads have been started
    thread_one.join()
    thread_two.join()
```


---

#### Concurrent Thread Pools (recommended)
```python
import time
import concurrent.futures
from typing import Callable


def time_execution(callback: Callable) -> Callable:
    def wrapper() -> None:
        start = time.perf_counter()
        callback()
        end = time.perf_counter()
        elapsed = round(end - start, 2)
        print(f"Time Elapsed: {elapsed}s")

    return wrapper


def slow_function(duration: float=0.5) -> str:
    time.sleep(duration)
    return f"[DONE] Duration {duration}s"


@time_execution
def main() -> None:
    # the executor will not exit until all threads complete
    with concurrent.futures.ThreadPoolExecutor() as executor:
        futures = [executor.submit(slow_function, 1) for _ in range(10)]

        # get results from threads as they complete
        for future in concurrent.futures.as_completed(futures):
            # error will be throws when fetching thread results
            try:
                result = future.result()
                print(result)
            except Exception as err:
                print("[error]", err)
```


---

#### Multiprocessing
Multiprocessing is useful when we have multiple CPU-Bound Operations. **Multiprocessing doesn’t help with IO-Bound Operations**.

Threading doesn’t actually run the code in parallel. When the CPU is idle (i.e. awaiting IO) the program will move on to the next instructions. In contrast, with multiprocessing we run code simultaneously on different processes. Figure shows multiprocessing in action.


##### Basic example (not recommended)
```python
import time
from typing import Callable
import multiprocessing


def time_execution(callback: Callable) -> Callable:
    def wrapper() -> None:
        start = time.perf_counter()
        callback()
        end = time.perf_counter()
        elapsed = round(end - start, 2)
        print(f"Time Elapsed: {elapsed}s")

    return wrapper


# some heavy CPU-bound operation
def slow_function(duration: float = 0.5) -> str:
    time.sleep(duration)
    return f"[DONE] Duration {duration}s"


@time_execution
def main() -> None:
    process_one = multiprocessing.Process(target=slow_function, args=(1.0,))
    process_two = multiprocessing.Process(target=slow_function, args=(0.5,))

    # start execution
    process_one.start()
    process_two.start()

    # wait for completion of each process before moving on; ensure you only join
    # after all processes have been started
    process_one.join()
    process_two.join()
```


---

##### Process pools
```python
import time
from typing import Callable
import concurrent.futures


def time_execution(callback: Callable) -> Callable:
    def wrapper() -> None:
        start = time.perf_counter()
        callback()
        end = time.perf_counter()
        elapsed = round(end - start, 2)
        print(f"Time Elapsed: {elapsed}s")

    return wrapper


# some heavy CPU-bound operation
def slow_function(duration: float = 0.5) -> str:
    time.sleep(duration)
    return f"[DONE] Duration {duration}s"


@time_execution
def main() -> None:
    # executor will only exit once all processes have completed
    with concurrent.futures.ProcessPoolExecutor() as executor:
        processes = [executor.submit(slow_function, 1.0) for _ in range(10)]

        for process in concurrent.futures.as_completed(processes):
            # error is throws when getting results, rather than during execution
            try:
                result = process.result()
                print(result)
            except Exception as err:
                print("[error]", err)
```

