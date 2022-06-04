#include "LogSender.hpp"
#include "FTP.hpp"

int main() {
    FTP * ftp = new FTP("127.0.0.1");
    LogSender l(ftp);

    return  0;
}