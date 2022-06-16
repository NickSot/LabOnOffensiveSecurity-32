#ifndef LOG_SENDER_H
#define LOG_SENDER_H

#include <string>
#include <fstream>
#include <winsock2.h>
#include <WS2tcpip.h>

//comment later
#include <iostream>

class LogSender {
	public:
		LogSender(sockaddr_in * pAddr);
		void send_logs(const char * filename);

	private:
		SOCKET sock;
		sockaddr_in * addr;
		std::string text = "";
};

#endif