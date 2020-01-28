#include <stdio.h>
#include "tcpclient.h"


using namespace std;
using namespace eLinux;


int main(int argc, const char** argv) {
	string msg = "GET / HTTP/1.1\r\n + Host: " + string(argv[1]) + "\r\n\r\n";
	string data;

	TCPClient client;
	client.connect(argv[1], atoi(argv[2]));
	client.send(msg);
	client.receive(data, 1024);
	printf("Data: %s", data.c_str());
}