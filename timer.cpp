// #include <windows.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <unistd.h>

int counter = 1;
std::mutex mtx;

bool ready = false;

void tick() {
	while (true) {
		if (counter > 180) 
			counter = 1;
		
		std::this_thread::sleep_for(std::chrono::seconds(1));

        mtx.lock();
        
        cout << counter << endl;
		counter++;

		ready = true;

        mtx.unlock();
	}
}