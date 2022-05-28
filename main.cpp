#include "LogSender.hpp"
#include "FTP.hpp"

int main() {
    LogSender l(new FTP());
    l.send_logs();

    return  0;
}