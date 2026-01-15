
#### Executors 

```java
package com.sandbox;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;

public class Main {
    private static int MAX_PARALLEL = 5;

    public static void main(String[] args) {
        List<Future<Integer>> futures = new ArrayList<>();
        try (ExecutorService executor = Executors.newFixedThreadPool(
	        MAX_PARALLEL, Thread.ofVirtual().factory())) {
        
            for (int i = 0; i <= 20; i++) {
                final int input = i;
                Future<Integer> futureResult = executor.submit(() -> {
                    return task(input);
                });
                System.out.printf("adding: %d\n", input);
                futures.add(futureResult);
            }

            executor.shutdown();
            executor.awaitTermination(20, TimeUnit.SECONDS);
        } catch (Exception ex) {
            System.err.println("error: " + ex.getMessage());
            System.exit(1);
        }

        /** we start fetching the results when the executor has shutdown. */
        for (Future<Integer> future : futures) {
            try {
                /** get() method blocks until the result is available. */
                Integer result = future.get();
                System.out.println(result);
            } catch (Exception ex) {
                System.err.println("error: " + ex.getMessage());
                System.exit(1);
            }
        }
    }

    private static int task(int n) throws Exception {
        Thread.sleep(1_000);
        return n * 2;
    }
}
```

**Note**: In the above example if we remove `Thread.ofVirtual().factory()`, the executor will use normal threads instead of virtual threads.
