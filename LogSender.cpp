#include "LogSender.hpp"

LogSender::LogSender(Protocol * protocol) {
	this->protocol = protocol;
}

void LogSender::send_logs(const char * filename) {
	protocol->send_file(filename);
}