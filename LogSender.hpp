#ifndef PROTOCOL_H
#define PROTOCOL_H
#endif

#include <string>
#include "Protocol.hpp"

class LogSender {
	public:
		LogSender(Protocol * protocol);
		void send_logs();

	private:
		Protocol * protocol;
		std::string text;
};