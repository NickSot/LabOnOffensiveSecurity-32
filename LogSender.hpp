#ifndef LOG_SENDER_H
#define LOG_SENDER_H

#include <string>
#include "Protocol.hpp"

class LogSender {
	public:
		LogSender(Protocol * protocol);
		void send_logs(const char * filename);

	private:
		Protocol * protocol;
		std::string text;
};

#endif