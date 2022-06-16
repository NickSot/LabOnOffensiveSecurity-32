#include <windows.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <unistd.h>


int counter = 1;
int prev_count;
std::mutex mtx;
void tick() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));

        mtx.lock();
        std::cout << counter << std::endl;
        prev_count = counter;
		counter++;
        mtx.unlock();
	}
}