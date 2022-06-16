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
		LogSender(sockaddr_in * pAddr);
		SOCKET send_logs();

	private:
		sockaddr_in * addr;
		std::string text = "";
};

#endif