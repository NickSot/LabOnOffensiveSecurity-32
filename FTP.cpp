#include "FTP.hpp"

FTP::FTP(const char * ip, const char * username, const char * password) {
	this->ip = ip;
    this->username = username;
    this->password = password;
}

void FTP::send_file(const char * filename) {    
    HINTERNET hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    
    DWORD timeout = 50;
    DWORD connection_retries = 0;

    InternetSetOption(hInternet, INTERNET_OPTION_CONNECT_TIMEOUT, &timeout, sizeof(DWORD));
    InternetSetOption(hInternet, INTERNET_OPTION_RECEIVE_TIMEOUT, &timeout, sizeof(DWORD));
    InternetSetOption(hInternet, INTERNET_OPTION_SEND_TIMEOUT, &timeout, sizeof(DWORD));

    InternetSetOption(hInternet, INTERNET_OPTION_CONNECT_RETRIES, &connection_retries, sizeof(DWORD));

    HINTERNET hFtpSession = InternetConnect(hInternet, ip, INTERNET_DEFAULT_FTP_PORT, username, password, INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);

    bool val = FtpPutFile(hFtpSession, string("." + string(filename)).c_str(), filename, FTP_TRANSFER_TYPE_ASCII, 0);

    InternetCloseHandle(hFtpSession);
    InternetCloseHandle(hInternet);
}