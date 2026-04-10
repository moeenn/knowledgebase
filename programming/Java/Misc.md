## Time function execution

```java
long start = System.nanoTime();
long sum = 0;
for (int i = 1; i <= 1_000_000_000; i++)
{
    sum += i;
}

long elapsed = (System.nanoTime() - start) / 1_000_000;
System.out.printf("Elapsed: %d ms\n", elapsed);
```

### A better approach

```java
import java.lang.AutoCloseable;

public class Timer implements AutoCloseable
{
    private String id;
    private long start;

    public Timer(String id)
    {
        this.id = id;
        start = System.nanoTime();
    }

    @Override
    public void close()
    {
        long end = System.nanoTime();
        long elapsed = (end - start) / 1_000_000;
        System.out.printf("[%s] Elapsed: %s ms\n", id, elapsed);
    }
}
```

**Note**: Java does not have C++ style destructors, `AutoCloseable` is the next best thing.

```java
try (var timer = new Timer("Billion loop"))
{
    someLongRunningFunction();
}
```
