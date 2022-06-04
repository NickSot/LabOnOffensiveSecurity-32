#ifndef SMTP_H
#define SMTP_H
#include "Protocol.hpp"

class SMTP : public Protocol {
	public:
		SMTP();
		void send_file(const char * filename);

	private:
		void create_socket(int & sock, const char* server_ip, const unsigned short server_port);
		void send_request(int sock, const char* buf_request);
		void send_all(int sock, const void *vbuf, size_t size_buf);
};

#endif

