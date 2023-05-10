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

