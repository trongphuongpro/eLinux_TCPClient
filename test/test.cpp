#include <stdio.h>
#include "tcpclient.h"


using namespace std;
using namespace eLinux;


int main(int argc, const char** argv) {
	string msg;

	TCPClient client;
	client.connect("192.168.7.2", 1234);

	msg = "Hello, I'm client";
	client.send(msg);
	client.receive(msg, 1024);
	printf(">> Receive: %s\n", msg.c_str());
}