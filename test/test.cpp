#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include "tcpclient.h"


using namespace std;
using namespace eLinux;


int main(int argc, const char** argv) {
	string msg;

	TCPClient client;
	client.connect("192.168.7.2", 1234);
	int ret;

	for (int i = 0; i < 10; i++) {
		ret = client.send("msg-"+to_string(i));
		printf("send: ret: %d error: %d\n", ret, errno);
		sleep(3);
		ret = client.receive(msg, 1024);
		printf("[Receive] %s\n", msg.c_str());
		printf("recv: ret: %d error: %d\n", ret, errno);

		puts("--------------------------------");
		sleep(3);
	}
}