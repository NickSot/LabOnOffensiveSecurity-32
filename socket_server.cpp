#include <winsock2.h>
#include <iostream>

using namespace std;

int main() {
	WSADATA wsaData;

    //----------------------
    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (sock == -1)
    {
        std::cout << "Failed to create socket descriptor. " <<  WSAGetLastError() << "\n";
        return 1;
    }

	sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("131.155.222.2");
	addr.sin_port = htons(5000);
	
	int bind_result = bind(sock, (sockaddr *)&addr, sizeof(addr));

	int new_conn = -1000;

	listen(sock, 100);

	while (true) {
		sockaddr_in client_addr;
		int client_size = sizeof(client_addr);

		if (new_conn == -1000)
			new_conn = accept(sock, (sockaddr *)&client_addr, &client_size);

		char buffer[1024];
		
		int result = recv(new_conn, buffer, 1024, 0);

		if (result > 0)
			cout << buffer << endl;
	}

	return 0;
}