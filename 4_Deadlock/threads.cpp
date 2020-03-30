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
		std::lock(mutex_, mutex2_);
		std::lock_guard<std::mutex> guard(mutex_, std::adopt_lock);
		std::lock_guard<std::mutex> guard2(mutex2_, std::adopt_lock);
		std::cout << msg << ": " << value << std::endl;
	}
	void shared_print2(std::string msg, int value)
	{
		std::lock(mutex_, mutex2_);
		std::lock_guard<std::mutex> guard(mutex_, std::adopt_lock);
		std::lock_guard<std::mutex> guard2(mutex2_, std::adopt_lock);
		std::cout << msg << ": " << value << std::endl;
	}
private:
	std::mutex     mutex_;
	std::mutex 	   mutex2_;
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
		log.shared_print2(std::string("From main: "), i);
	t1.join();
	return 0;
}
