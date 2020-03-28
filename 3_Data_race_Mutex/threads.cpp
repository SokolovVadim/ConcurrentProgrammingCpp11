#include <thread>
#include <iostream>
#include <string>
#include <mutex>
#include <fstream>


// std::mutex mtx;

/*void shared_print(std::string msg, int id)
{
	mtx.lock();
	std::cout << msg << id << std::endl;
	mtx.unlock();
}*/

// RAII

/*void shared_print(std::string msg, int id)
{
	std::lock_guard<std::mutex> guard(mtx);
	std::cout << msg << id << std::endl;
}*/

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
		std::lock_guard<std::mutex> guard(mutex_);
		fout_ << msg << ": " << value << std::endl;
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
