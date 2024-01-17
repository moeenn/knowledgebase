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