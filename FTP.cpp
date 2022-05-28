#include "FTP.hpp"
#include <iostream>

using namespace std;

// implement the proper initializations
FTP::FTP() {
	this->port = 21;
}

//implement the sending logic
void FTP::send(int * message) {
	cout << "sent file" << endl;
}

//implement the receiving logic
int * FTP::receive() {
	cout << "received file" << endl;
}