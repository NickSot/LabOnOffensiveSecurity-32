#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <string>
#include <fstream>
#include <iostream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wininet.h>

using namespace std;

class Protocol {
	public:
		Protocol () {};
		virtual void send_file(const char * filename) = 0;
};

#endif