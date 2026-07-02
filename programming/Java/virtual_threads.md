## Basic Example

```java
public class LongRunningTask implements Runnable {
    final String id;

    public LongRunningTask(String id) {
        this.id = id;
    }

    public void run() {
        try {
            System.out.printf("[%s] starting...\n", id);
            Thread.sleep(1_000);
            System.out.printf("[%s] complete.\n", id);
        } catch (Exception e) {
            System.err.printf("[%s] error: %s.\n", id, e.getMessage());
        }
    }
}
```

```java
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    private static void run() throws Exception {
        try (ExecutorService exec = Executors.newVirtualThreadPerTaskExecutor()) {
            final int limit = 1_000;
            for (int i = 0; i < limit; i++) {
                var task = new LongRunningTask(String.format("action-%d", i));
                exec.submit(task);
            }
        }
    }

    public static void main(String[] args) {
        try {
            Main.run();
        } catch (Exception e) {
            System.err.printf("error: %s.\n", e.getMessage());
        }
    }
}
```