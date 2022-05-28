#ifndef PROTOCOL_H
#define PROTOCOL_H
#include "Protocol.hpp"
#endif

class FTP : public Protocol {
	public:
		FTP();
		int * receive();
		void send(int * message);
};