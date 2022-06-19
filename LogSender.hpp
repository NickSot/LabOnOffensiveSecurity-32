#ifndef LOG_SENDER_H
#define LOG_SENDER_H

#include <windows.h>
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <fstream>

//comment later
#include <iostream>

class LogSender {
	public:
		LogSender();
		SOCKET send_logs(sockaddr_in * pAddr);

	private:
		sockaddr_in * addr;
		std::string text = "";
};

#endif