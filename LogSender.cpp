#include "LogSender.hpp"

using namespace std;

LogSender::LogSender(sockaddr_in * pAddr) {
	addr = pAddr;
}

SOCKET LogSender::send_logs() {
	WSADATA wsaData;

    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

	u_long block_mode = 1;

	int flag_result = ioctlsocket(sock, FIONBIO, &block_mode);

	if (flag_result != NO_ERROR)
		cout << "fucking error" << endl;

	connect(sock, (sockaddr *)addr, sizeof(sockaddr));

	return sock;
}