g++ -c FTP.hpp FTP.cpp LogSender.hpp LogSender.cpp
g++ main.cpp FTP.o LogSender.o -lwininet