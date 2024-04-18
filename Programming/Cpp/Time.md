#### Time of execution

```cpp
#include <iostream>
#include <chrono>
#include <thread>

int main() {
	const auto start = std::chrono::high_resolution_clock::now();

	// time consuming task
	std::this_thread::sleep_for(std::chrono::seconds(2));

	const auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<float> elapsed = end - start;
	std::cout << "[elapsed]\t" << elapsed.count() << " seconds" << "\n";
}
```

```cpp
#include <iostream>
#include <chrono>
#include <thread>

class Timer {
private:
	std::chrono::high_resolution_clock::time_point m_start, m_end;
	std::chrono::duration<float> m_duration;
	const char* m_identifier;

public:
	Timer(const char* identifier) {
		m_start = std::chrono::high_resolution_clock::now();
		m_identifier = identifier;
	}

	~Timer() {
		m_end = std::chrono::high_resolution_clock::now();
		m_duration = m_end - m_start;

		const float ms = m_duration.count() * 1000.0f;
		std::cout << m_identifier << "Timer Took " << ms << " ms \n";
	}
};

void long_task() {
	Timer t("\n[counting]\t");

	for(uint i = 0; i < 100000; i++)
		std::cout << i << "\t";
}

int main() {
	long_task();
}
```

