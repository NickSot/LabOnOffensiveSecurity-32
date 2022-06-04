#include "SMTP.hpp"

SMTP::SMTP() {
	WSADATA WSData;
    SOCKET sock;

    struct sockaddr_in addr;

    WSAStartup(MAKEWORD(1, 1), &WSData);

    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    addr.sin_family = AF_INET;
    addr.sin_port = htons(25);
    
    hostent *server_adress = gethostbyname("smtp.gmail.com");
    addr.sin_addr.s_addr = *((unsigned long *)server_adress->h_addr_list[0]);   
    
    int con = connect(sock, (struct sockaddr *) &addr, sizeof(addr));
    cout << "connect status " << con << '\n';
}

void SMTP::send_file(const char * filename) {
	printf(filename);
}