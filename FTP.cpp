#include "FTP.hpp"

#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <unistd.h>
#include <sys/types.h>

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

// implement the proper initializations
FTP::FTP(const char * ip_address) 
{
	this->sock_data = 0;
	this->sock_ctrl = 0;
	this->port = 21;

	create_socket(sock_data, this->ip_address.c_str(), port);
}

//implement the sending logic
void FTP::send_file(const char * filename) {
	char * buf_request;

	sprintf(buf_request, "APPE %s\r\n", filename);

	send_request(sock_data, buf_request);
}

void FTP::create_socket(int &sock, const char* server_ip, const unsigned short server_port)
{
	// server address
	struct sockaddr_in server_addr;

	// construct the server address structure
	memset(&server_addr, 0, sizeof(server_addr));// zero out structure
	server_addr.sin_family = AF_INET;// internet address family
	server_addr.sin_addr.s_addr = inet_addr(server_ip);// server IP address
	server_addr.sin_port = htons(server_port);// server port

	// create a stream socket using TCP
	if ((sock = ::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		std::cout << strerror(sock) << endl;
	}

	int code = ::connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));

	// establish the connection to the server
	if (code < 0)
	{
		std::cout << "connect error: " << strerror(code) << std::endl;
		std::cout << code << endl;
		exit(1);
	}
}

void FTP::send_request(int sock, const char* buf_request)
{
  std::cout << "request: " << buf_request << std::endl;

  //send 
  send_all(sock, (void *)buf_request, strlen(buf_request));
  return;
}

void FTP::send_all(int sock, const void *vbuf, size_t size_buf)
{
  const char *buf = (char*)vbuf;	// can't do pointer arithmetic on void* 
  int send_size; // size in bytes sent or -1 on error 
  int size_left; // size left to send 
  const int flags = 0;

  size_left = size_buf;
  while (size_left > 0)
  {
    if ((send_size = send(sock, buf, size_left, flags)) == -1)
    {
      std::cout << "send error: " << std::endl;
    }
    size_left -= send_size;
    buf += send_size;
  }
  return;
}