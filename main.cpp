#include "LogSender.hpp"
#include "FTP.hpp"

int main() {
    FTP * ftp = new FTP("127.0.0.1", "kolio", "099824058");
    LogSender l(ftp);
    
    l.send_logs("/_.txt");

    return  0;
}