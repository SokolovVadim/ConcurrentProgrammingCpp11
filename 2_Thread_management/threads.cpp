#include <thread>
#include <iostream>
#include <string>


void worker(){
	std::cout << "It's corona time" << std::endl;
}


// Lambda
class Functor1
{
public:
	void operator()(){
		for(int i(0); i > -100; i--)
			std::cout << "job from t1 " << i << std::endl;
	}
};

class Functor2
{
public:
	void operator()(std::string msg){
		std::cout << "t1 says: " << msg << std::endl;
	}
};

int main()
{
	// Functor fct;
	// std::thread thread_1(fct);
	
	// std::thread thread_1(Functor()); This line isn't compilable
	// std::thread thread_1((Functor1())); it works

	std::string msg = "Watch out and wash hands";
	std::thread thread_1((Functor2()), msg);

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
