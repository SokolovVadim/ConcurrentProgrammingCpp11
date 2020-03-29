# Unique lock and Lazy initialization

## Unique lock
```
class LogFile{
	// ...
void shared_print(std::string msg, int value)
	{
		std::unique_lock<std::mutex> guard(mutex_, std::defer_lock);

		// do smth that doesn't require fout_

		guard.lock();
		fout_ << msg << ": " << value << std::endl;
		guard.unlock();

		// do smth that doesn't require fout_

		guard.lock();

		std::unique_lock<std::mutex> guard2 = std::move(guard); // it's only allowed to move lock neither copy
	}
private:
	std::mutex    mutex_;
	std::ofstream fout_;
};
```