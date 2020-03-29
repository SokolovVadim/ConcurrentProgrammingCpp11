#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <fstream>

class LogFile{
public:
	LogFile()
	{
		fout_.open("log.txt");
	}
	~LogFile()
	{
		fout_.close();
	}
	void shared_print(std::string msg, int value)
	{
		// std::lock_guard<std::mutex> guard(mutex_);
		// std::unique_lock<std::mutex> guard(mutex_);
		std::unique_lock<std::mutex> guard(mutex_, std::defer_lock);

		// do smth that doesn't require fout_

		guard.lock();
		fout_ << msg << ": " << value << std::endl;
		guard.unlock();

		// do smth that doesn't require fout_

		guard.lock();

		std::unique_lock<std::mutex> guard2 = std::move(guard);

	}

private:
	std::mutex    mutex_;
	std::ofstream fout_;
};

void worker(LogFile & log){
	for(int i(0); i > -100; i--)
		log.shared_print(std::string("job from t1 "), i);
}

int main()
{
	LogFile log;
	std::thread t1(worker, std::ref(log));
	for(int i(0); i < 100; ++i)
		log.shared_print(std::string("From main: "), i);
	t1.join();
	return 0;
}
