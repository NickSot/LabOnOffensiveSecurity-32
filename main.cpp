// threads
// mutex

#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <stdlib.h>
#include "timer.cpp"
//#include <unistd.h>



extern int counter;
extern std::mutex mtx;

std::once_flag zeroFlag;


// using namespace std;

int main() {
	std::thread th(tick);

    while (true){


        if(mtx.try_lock())

            if (counter % 180 == 0){
                std::cout << "five" << std::endl;
            }

            else if (counter%60 == 0){

                std::cout << "five" <<std::endl;
                
            }
           
            mtx.unlock();
            sleep(1);

        }
        
   
	th.join();

	return 0;
}



