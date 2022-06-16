#include "LogSender.hpp"

using namespace std;

LogSender::LogSender(sockaddr_in * pAddr) {
	addr = pAddr;
	this->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void LogSender::send_logs(const char * filename) {
	WSADATA wsaData;

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	ifstream f;

	f.open(filename);

	if (f.is_open()) {
		while (getline(f, text)) {
			
		}

		f.close();
	}

	// int iTimeout = 1;
 //    int iRet = setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char *)&iTimeout, sizeof(iTimeout) );
 //    cout << iRet << endl;

	int result = connect(sock, (sockaddr *)addr, sizeof(sockaddr));
	
	cout << "error" << endl;

	if (result == -1) {
		return;
	}

	int send_result = send(sock, text.c_str(), strlen(text.c_str()), 0);

	result = closesocket(sock);
}