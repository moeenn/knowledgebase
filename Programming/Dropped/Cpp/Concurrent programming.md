#### Terminology

**Process**: The overall instance of a program being executed. It contains all the details about the program that are necessary for its execution e.g. binary location, process id (`PID`), state etc. 

**Thread**: Thread of execution is the smallest sequence of instructions that can be managed independently by a scheduler. Multiple threads of execution can exist within a single process.

**Inter-process Communication Channels**: E.g. Files, Types, Message Queues etc

**Over-subscription**: A situation where our program requests more threads than the hardware can run concurrently.

**Race Condition**: A situation where the outcome of a program depends upon the relative execution order of one or more threads.

**Multi-processing**: Independent Processes exist each with its own single thread. The processes communicate using inter-process communication (IPC) channels. 

**Multi-threading**: A single process exists with many threads. The processes communicate with each other through Shared Memory. Multi-threading is generally faster than Multi-processing.


---

#### Example

```cpp
#include <array>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#define MAX_THREADS 3
void action(const std::string &msg);

int main() {
  std::array<std::thread, MAX_THREADS> threads{
      std::thread(action, "Alsa"),
      std::thread(action, "Binutils"),
      std::thread(action, "Reaper"),
  };

  /**
   *  join all threads on main thread
   *  i.e. wait for threads to complete
   */
  for (auto &t : threads)
    if (t.joinable())
      t.join();
}

void action(const std::string &msg) {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "[thread]\t" << msg << " [Done]\n";
}
```

**Note**: If we need to use Multi-threading in our program we need to include the `-pthread` in our `Makefile` compilation flags.


---

#### Passing values by Reference
Even if the Callable Object accepts arguments by reference, by default the arguments will always be passed by value to the callable object by the Thread. This means that by default the threads will receive a copy of the arguments. This behavior can be changed by using the `std::ref()` function.

```cpp
#include <iostream>
#include <thread>

// function received arguments by reference
// when function is called by a Thread, arguments will be passed by value
// compiler will not allow omission of this const
void action(const std::string& msg) {
	std::cout << "[thread]\t" << msg << "\n";
}

int main() {
	std::string msg = "c++ go br br br";

	std::thread t1(action, msg);
	t1.join();
}
```

**Note**: Newer versions of the GCC will not allow you to modify the value of Arguments within the Function (or any other callable object that is called by a Thread). It will not even allow us to omit the keyword const from the Function Prototype, unless we do the following.

```cpp
void action(std::string& msg) {
	std::cout << "[thread]\t" << msg << "\n";
	msg = "assembly goes br br br";
}

int main() {
	std::string msg("c++ goes br br br");

	std::thread t1(action, std::ref(msg));
	t1.join();

	std::cout << "[main]\t\t" << msg << "\n";
}

// [thread]        c++ goes br br br
// [main]          assembly goes br br br
```


---

#### Hardware supported threads
We can request an **estimate** of the number of Threads that our hardware will be able to run concurrently.

```cpp
int main() {
	uint max_threads = std::thread::hardware_concurrency();
	std::cout << "[main]\t\t" << max_threads << "\n";
}
// 4
```


---

#### Handling Exceptions
Consider a scenario where multiple Threads are running and the main Thread throws an Exception. Due to the Exception the subsequent Threads will not be able to Join with the main Thread and will be destroyed. 

There are couple of ways we can handle this situation
- Using Try-Catch Block
- Using Resource Acquisition Is Initialization (`RAII`) Approach


##### Try-Catch Approach
```cpp
#include <iostream>
#include <thread>
#include <array>

#define MAX_THREADS 3

void action(const char* msg) {
	std::cout << "[msg]\t" << msg << "\n";
}

int main() {
	std::array<std::thread, MAX_THREADS> threads;
	std::array<const char*, MAX_THREADS> names = {
            "alsa", "binutils", "reaper"
      };

	// create all threads
	for(uint i = 0; i < MAX_THREADS; i++)
		threads.at(i) = std::thread(action, names.at(i));

	// if an exception is thrown by main thread, the other
	// threads will not not be able to join and will be destroyed
	try {
		for(uint i = 0; i < 100; i++)
			std::cout << "[main]\t performing some task ...\n";
	} catch (const std::runtime_error& err) {
		// join subsequent threads here
		for(uint i = 0; i < MAX_THREADS; i++) {
			if(threads.at(i).joinable())
				threads.at(i).join();
		}

		std::cerr << "[error]\t" << err.what() << "\n";
	}

	// threads will be joined if not already joined
	for(uint i = 0; i < MAX_THREADS; i++) {
		if(threads.at(i).joinable())
			threads.at(i).join();
	}
}
```


---

#### Mutual Exclusion (Mutex)
In the event a single resource needs to be accessed by multiple threads, there needs to be a way to ensure that only one thread can use the resource at any given time. Mutex Locks are used to achieve this.

```cpp
#include <iostream>
#include <thread>
#include <mutex>

std::mutex mu;

void shared_display(const char* msg, int id) {
	mu.lock();
	std::cout << msg << id << "\n";
	mu.unlock();
}

void action() {
	for(int i = 0; i > -100; i--)
		shared_display("[thr]\t", i);
}

int main() {
	std::thread t1(action);

	for(uint i = 0; i < 100; i++)
		shared_display("[man]\t", i);

	t1.join();
}
```

In the above code, the resource being shared by our Two Threads is the Console. Whichever Thread holds the Mutex Lock will be able to print out messages to the Console.

The above code demonstrates the mechanism but it isn’t safe. There are couple of problems with this code:
- In scenarios where the red highlighted line throws an Exception, the Mutex will never be unlocked. This means that resources will remain tied up and will not be freed.
- The Shared Resource i.e. Console can still be accessed manually which will bypass the Mutex Lock.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

class Log {
Private:
      // initialize Mutex
	std::mutex m_mutex;
	std::ofstream m_logfile;

public:
	Log(const char* filename) {
		m_logfile.open(filename);
	}

	~Log() {
		m_logfile.close();
	}

	void write(const char* msg, int id) {
		std::lock_guard<std::mutex> guard(m_mutex);	// RAII
		m_logfile << msg << "\t" << id << "\n";
	}
};

void action(Log& log) {
	for(int i = 0; i > -100; i--)
		log.write("[thread]", i);
}

int main() {
	Log log("log.txt");
	std::thread t1(action, std::ref(log));

	for(uint i = 0; i < 100; i++)
		log.write("[main]", i);

	t1.join();
}
```

- The Resource being shared between threads is the Log File
- We have completely encapsulated the Log File inside its Class, making it private so it can’t be accessed in an unsafe manner. 
- Every time a thread writes a message to the file it temporarily acquires the Mutex Lock
- `std::lock_guard` is simply a Wrapper Class that executes the `std::mutex::lock()` when lock is acquired by a thread and executes `std::mutex::unlock()` when the guard object goes out of scope.
- The Log File needs to be modified by our threads. Recall that by default threads are provided Copies of Arguments even when the threaded function accepts arguments by reference.
- We need to ensure that the threaded function i.e. action() is provided reference to the Log File so the thread is able to modify it. We explicitly specify this by using the `std::ref()` Function.

**Note**
`std::mutex` has the benefits of being platform independent. Different Operating Systems use different mechanisms for Mutual Exclusions e.g. Linux and Unix use `pthreads`, Windows uses some proprietary stuff. With `std::mutex` we don't need to worry about the underlying implementation. 

In certain online examples you may see `pthread_mutex_t` which was the standard `POSIX` way of doing Mutual Exclusions on Linux / Unix before C++ standard library introduced `std::mutex`. These should be avoided.


---

#### Deadlock
Consider a situation where a single resource is protected by multiple Mutexes. Deadlock will occur when competing threads try to acquire a lock that is held by another thread. 

```cpp
#include <iostream>
#include <mutex>
#include <fstream>
#include <thread>

class Log {
private:
	std::mutex m_mutex;
	std::mutex m_mutex2;
	std::ofstream m_logfile;

public:
	Log(const char* filename) {
		m_logfile.open(filename);
	}

	~Log() {
		m_logfile.close();
	}

	void Write(const uint& msg) {
		std::lock_guard<std::mutex> guard(m_mutex);
		std::lock_guard<std::mutex> guard2(m_mutex2);
		m_logfile << "[thread]\t" << msg << "\n";
	}

	void Write2(const uint& msg) {
		std::lock_guard<std::mutex> guard2(m_mutex2);
		std::lock_guard<std::mutex> guard(m_mutex);
		m_logfile << "[thread2]\t" << msg << "\n";
	}

};

void action(Log& log) {
	for(uint i = 0; i < 10000; i++)
		log.Write(i);
}

void action2(Log& log) {
	for(uint i = 0; i < 10000; i++)
		log.Write2(i);
}

int main() {
	Log log("dump.txt");

	std::thread t1(action, std::ref(log));
	std::thread t2(action2, std::ref(log));

	t1.join();
	t2.join();
}
```

- Thread `t1` attempts to lock Mutex `m_mutex` first and then `m_mutex2`
- Thread `t2` attempts to lock Mutex `m_mutex2` first and then `m_mutex`
- At some point both threads get stuck waiting for the other thread to release a Mutex Lock that cannot be released. The execution of both threads will be stuck indefinitely.

There are two ways to avoid a Deadlock
1. Deadlock can be easily avoided by ensuring that every thread locks and unlocks the `Mutex` in the same order.
2. We can implement `std::lock()` function.

```cpp
// Write method inside Log Class
void Write(const uint& msg) {
	std::lock(m_mutex, m_mutex2);
	std::lock_guard<std::mutex> guard(m_mutex, std::adopt_lock);
	std::lock_guard<std::mutex> guard2(m_mutex2, std::adopt_lock);

	m_logfile << "[thread]\t" << msg << "\n";
}
```

**Note**: To keep the code manageable, it is recommended that only one Mutex be locked at any given time.


---

#### Unique Lock
Unique Lock is similar to `std::lock_guard` except it is more flexible.
- `std::unique_lock` can be manually locked and unlocked. These options are not present with `std::lock_guard`.
- Locking of the `std::unique_lock` can be deferred at the time the lock object is initialized. `std::lock_guard` is locked at initialization.
- Locker Objects i.e. `std::lock_guard` and `std::unique_lock` cannot be copied but they can be  moved using the `std::move` function. 

```cpp
// Write method inside the Log Class
void Write(const uint& msg) {
	std::unique_lock<std::mutex> guard(m_mutex, std::defer_lock);
	//
	// perform some non-mutex related tasks here
	//

	// manually lock the previously deferred lock
	guard.lock();
	m_logfile << "[thread]\t" << msg << "\n";

	// option not present in std::lock_guard
	guard.unlock();
}
```

**Note**: `std::unique_lock` is more flexible compared with the `std::lock_guard` but it also uses more resources.


---

#### Lazy Initialization
Lazy initialization means that a Resource should only be opened / initialized upon first use. In our Log example above we Open the Log file when the Log object is initialized. If we don’t call the Write() method then we end up opening the Log file for nothing.

```cpp
// TODO: specify default filename in header files
Log(const char* filename) {
	m_logfile_name = filename;
}

void Write(const uint& msg) {
      // open the log file if not already opened
	if(! m_logfile.is_open())
		m_logfile.open(m_logfile_name);

	std::lock_guard<std::mutex> guard(m_write_mutex);
	m_logfile << "[thread]\t" << msg << "\n";
}
```

The above code works but is inefficient in the manner that the log file could be opened multiple times by multiple threads. The complete code with a better implementation is as follows

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

class Log {
private:
	std::mutex m_write_mutex;
	const char* m_logfilename;
	std::ofstream m_logfile;
	std::once_flag m_once_flag;

public:
	Log(const char* filename) {
            // lazy initialization
		m_logfilename = filename;
	}

	~Log() {
		m_logfile.close();
	}

	void Write(const char* msg, const uint& num) {
		// log file only needs to be opened once
		// following lambda function will only be called once
		// and by only one thread
		std::call_once(m_once_flag, [&](){
			m_logfile.open(m_logfilename, std::ios::app);
		});

		std::lock_guard<std::mutex> guard(m_write_mutex);
		m_logfile << msg << "\t" << num << "\n";
		std::cout << msg << "\t" << num << "\n";
	}
};

// driver function
void populate(Log& log, const char* msg) {
	for(uint num = 0; num < 1000; num++) {
		log.Write(msg, num);
	}
}

int main() {
	Log log("data.txt");

	std::thread t1(populate, std::ref(log), "[thread1]");
	std::thread t2(populate, std::ref(log), "[thread2]");

	t1.join();
	t2.join();
}
```


---

#### Condition Variable
```cpp
#include <iostream>
#include <thread>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

void populate() {
	for(int count = 10; count > 0; count--) {
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);
		locker.unlock();

		// notify one waiting threads
		// to notify all waiting threads use notify_all()
		cond.notify_one();

		// sleep for 1 second
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}

void consume() {
	for(int data = 0; data != 1; ) {
		std::unique_lock<std::mutex> locker(mu);

		// sleep thread until notified by other thread
		// lock is provided as argument which will be unlocked
		// by the condition variable
		cond.wait(locker, [](){
			return !q.empty();
		});
		// spurious wake: it is possible that the thread will wake up
		// without being notified by the other thread. The provided
		// lambda function ensures that the if this thread wakes up
		// spuriously, it is sent back to sleep

		// proceed with consumption of data
		data = q.back();
		q.pop_back();
		locker.unlock();
		std::cout << "[thread] Acquired value from Deque: " << data << "\n";
	}
}

int main() {
	std::thread t1(populate);
	std::thread t2(consume);

	t1.join();
	t2.join();
}
```


---

#### Threading
We can use Multi-threading split off execution of code from the main thread.

```cpp
#include <thread>

static bool is_finihed = false;

void task() {
	using namespace std::literals::chrono_literals;
	std::cout << "Creating Thread id " 
                << std::this_thread::get_id() << std::endl;

	while(! is_finihed) {
		std::cout << "Performing Task" << std::endl;
		std::this_thread::sleep_for(1s);
	}
}

int main() {
	std::thread worker(task);

	// wait for enter on main thread
	std::cin.get();
	is_finihed = true;

	worker.join();
	std::cout 	<< "Finished Tasks! \nClosing Main thread id "
			<< std::this_thread::get_id() << std::endl;
}
```

