#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <stdlib.h>
#include "file_send.cpp"
#include "timer.cpp"

extern int counter;
extern std::mutex mtx;

void send_logs(LogSender l) {
    l.send_logs("./_.txt");
}

int main() {
	std::thread th(tick);

    while (true){

        if(mtx.try_lock()) {

            if (counter % 10 == 0){
                send_file();
            }

            else if (counter % 60 == 0){
                std::cout << counter <<std::endl;
            }
           
            mtx.unlock();
            sleep(1);
        }
    }

	return 0;
}