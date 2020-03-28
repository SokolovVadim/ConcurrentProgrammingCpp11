#include <thread>
#include <iostream>


void worker(){
	std::cout << "It's corona time" << std::endl;
}


// Lambda
class Functor
{
public:
	void operator()(){
		for(int i(0); i > -100; i--)
			std::cout << "job from t1 " << i << std::endl;
	}
};

int main()
{
	Functor fct;
	std::thread thread_1(fct);
	// std::thread thread_1(worker); // t1 starts running
	// using RAII
	// Wrapper
	try{
		for(int i(0); i < 100; ++i)
			std::cout << "job from main: " << i << std::endl;
	} catch(...){
		thread_1.join();
		throw;
	}

	return 0;
}
