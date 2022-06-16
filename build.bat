g++ -c LogSender.hpp LogSender.cpp
g++ main.cpp LogSender.o -lwsock32 -o keylogger.exe