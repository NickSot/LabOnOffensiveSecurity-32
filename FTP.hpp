#ifndef PROTOCOL_H
#define PROTOCOL_H
#include "Protocol.hpp"
#endif


class FTP : public Protocol {
	public:
		FTP(const char * ip_address);
		void send_file(const char * filename);
	private:
		int sock_ctrl;
		int sock_data;
		void create_socket(int & sock, const char* server_ip, const unsigned short server_port);
		void send_request(int sock, const char* buf_request);
		void send_all(int sock, const void *vbuf, size_t size_buf);
};