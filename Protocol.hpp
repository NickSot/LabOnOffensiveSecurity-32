#include <string>

class Protocol {
	public:
		Protocol () {};
		virtual void send_file(const char * filename) = 0;
		
	protected:
		unsigned int port;
		std::string ip_address;
};