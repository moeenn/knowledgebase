```java
/** file: ThreadTask.java */
package com.app;

public class ThreadTask implements Runnable {

  @Override
  public void run() {
    int activeThreads = Thread.activeCount();
    System.out.println("Active Threads: " + activeThreads);

    String threadName = Thread.currentThread().getName();
    System.out.println("Starting new thread: " + threadName);

    try {
      Thread.sleep(3000);
    } catch (InterruptedException ex) {
      ex.printStackTrace();
    }

    System.out.println("End thread: " + threadName);
  }
}
```

```java
/** file: Main.java */
package com.app;
 
public class Main {
  public static void main(String... args) {
    Thread t1 = new Thread(new ThreadTask(), "sample thread # 1");
    Thread t2 = new Thread(new ThreadTask(), "sample thread # 2");
    Thread t3 = new Thread(new ThreadTask(), "sample thread # 3");

    /** start thread 1 & 2 */
    t1.start();
    t2.start();

    /** wait for thread 1 to finish before starting thread 3 */
    try {
      t1.join();
    } catch (InterruptedException ex) {
      ex.printStackTrace();
    }

    t3.start();
  }
}
```


---

#### Volatile
Threads can have local copies of variables (in thread cache), and the data does not have to be the same as the data held in other threads. The keyword `volatile` ensures that a member variable is always read from `main` memory and not cached to process memory.

**Note**: `volatile` does **not** implement any locking (i.e. `mutex`) mechanisms.  

```java
public class Game {
  /**
   * member variable which will be modified my multiple threads (i.e. Players)
   * volatile makes this variable atomic i.e. thread-safe
   * 
   * Without volatile, the counter variable may be cached in the CPU registers, 
   * and each thread may have its own local copy. As a result, one player 
   * thread may update the counter, but other threads may not immediately see 
   * the updated value due to caching.
   */
  private static volatile int counter = 0;

  public static class Player extends Thread {
    public Player(String name) {
      super(name);
    }

    @Override
    public void run() {
      for (int i = 0; i < 1000; i++) {
        counter++;
        System.out.printf("%s: %d\n", getName(), counter);
      }
    } 
  }
}
```

```java
import java.util.ArrayList;

public class Main {
  public static void main(String[] args) {    
    ArrayList<Game.Player> players = new ArrayList<>() {
      {
        add(new Game.Player("Player one"));
        add(new Game.Player("Player two"));
      }
    };

    players.stream().forEach(p -> p.start());
  }
}
```


---

#### Synchronized

`synchronized` obtains and releases locks on monitors which can force only one thread at a time to execute a code block. `synchronized` also synchronizes memory between thread cache and main memory. This means `synchronized` has a higher overhead than `volatile`.

We can use the synchronized keyword on different levels:
- Instance methods
- Static methods
- Code blocks

```java
package com.sandbox;

public class SyncCounter {
  private int sum = 0;

  public int getSum() {
    return sum;
  }

  public void increment() {
    sum += 1;  
  }
}
```

```java
package com.sandbox;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.stream.IntStream;

import org.junit.jupiter.api.Test;

public class SyncCounterTest {
  private static final int MAX_THREADS = 4;
  private static final int RETRIES = 1000;

  @Test
  public void testAdd() throws InterruptedException {
    ExecutorService threadpool = Executors.newFixedThreadPool(MAX_THREADS);
    SyncCounter counter = new SyncCounter();

    /** multiple threads incrementing the counter, all at once */
    IntStream
      .range(0, RETRIES)
      .forEach((n) -> threadpool.submit(counter::increment));

    /** this can throw InterruptedException */
    threadpool.awaitTermination(1000, TimeUnit.MILLISECONDS);

    /** this will fail because of race-condition in our program */
    assertEquals(1000, counter.getSum());
  }
}
```

In order to fix the race-condition in our program, we must mark the `increment` instance method as `synchronized`.

```java
public class SyncCounter {
  ...

  public synchronized void increment() {
    sum += 1;  
  }
}
```

If we don't want to mark the entire instance methods as `synchronized`, we can also mark specific blocks inside a method as `synchronized`.

```java
public class SyncCounter {
  ...

  public void increment() {
    // Some other un-synchronized code here.
    
    synchronized (this) {
      sum += 1;  
    }
  }
}
```
