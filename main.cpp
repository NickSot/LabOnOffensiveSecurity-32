// threads
// mutex

#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <stdlib.h>
#include "timer.cpp"
#include "file_send.cpp"

extern int counter;
extern std::mutex mtx;

int main() {
	std::thread th(tick);

    while (true){

        if(mtx.try_lock()) {

            if (counter % 180 == 0){
                std::cout << "five" << std::endl;
            }

            else if (counter%60 == 0){

                std::cout << "five" <<std::endl;
                
            }
           
            mtx.unlock();
            sleep(1);

        }


    }

	return 0;
}



