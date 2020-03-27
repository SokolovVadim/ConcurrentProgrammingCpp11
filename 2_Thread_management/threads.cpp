#include <thread>
#include <iostream>


void worker(){
	std::cout << "It's corona time" << std::endl;
}


int main()
{
	std::thread thread_1(worker); // t1 starts running
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
