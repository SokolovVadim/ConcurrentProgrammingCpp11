#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <fstream>

class LogFile{
public:
	LogFile()
	{}
	~LogFile()
	{
		fout_.close();
	}
	void shared_print(std::string msg, int value)
	{/*
		if(!fout_.is_open())
		{
			std::unique_lock<std::mutex> guard2(mutex_open_);
			fout_.open("log.txt");
		}*/

		// file will be opened only once by one thread
		std::call_once(flag_, [&](){ fout_.open("log.txt"); });

		std::unique_lock<std::mutex> guard(mutex_, std::defer_lock);
		mutex_.lock();
		fout_ << msg << ": " << value << std::endl;
		mutex_.unlock();
	}

private:
	std::once_flag flag_;
	// std::mutex    mutex_open_;
	std::mutex     mutex_;
	std::ofstream  fout_;
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
