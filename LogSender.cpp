#include "LogSender.hpp"

LogSender::LogSender(Protocol * protocol) {
	this->protocol = protocol;
}

void LogSender::send_logs() {
	// rework... convert the log of the log sender to
	// an integer array

	int message [] = {92};
	protocol->send(message);
}