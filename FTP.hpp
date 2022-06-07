#ifndef FTP_H
#define FTP_H
#include "Protocol.hpp"

#pragma comment(lib, "Wininet")

class FTP : public Protocol {
	public:
		FTP(const char * ip, const char * username, const char * password);
		void send_file(const char * filename);

	private:
		const char * username;
		const char * password;
		const char * ip;

		void create_socket(int & sock, const char* server_ip, const unsigned short server_port);
		void send_request(int sock, const char* buf_request);
		void send_all(int sock, const void *vbuf, size_t size_buf);
};

#endif

