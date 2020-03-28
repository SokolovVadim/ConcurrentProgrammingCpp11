# Data Race & Mutex

## Data race  
## Mutex
```
std::mutex mtx;

void shared_print(std::string msg, int id)
{
	mtx.lock();
	std::cout << msg << id << std::endl;
	mtx.unlock();
}
```

## RAII  
```
lass LogFile{
public:
	...
	void shared_print(std::string msg, int value)
	{
		std::lock_guard<std::mutex> guard(mutex_);
		fout_ << msg << ": " << value << std::endl;
	}
private:
	std::mutex    mutex_;
	std::ofstream fout_;
};
```
Never return fout to the outside workspace  

`ofstream& getStream() {return fout;}`

Never pass fout as an argument to user provided functions

```
void processf(void fun(ofstream&)){
	fun(fout); // it can do anything with fout (close, copy etc)
}
```
