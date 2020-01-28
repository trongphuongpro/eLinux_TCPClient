/**
 * @file tcpclient.cpp
 * @brief 
 * @author Nguyen Trong Phuong
 * @date 2020 Jan 28
 */


#include "tcpclient.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>


using namespace std;

namespace eLinux {

TCPClient::TCPClient() {
	this->socketfd = -1;
	this->server = NULL;
	this->__isConnected = false;
}


TCPClient::TCPClient(string server, int port) {
	this->socketfd = -1;
	this->server = NULL;
	this->__isConnected = false;
	this->serverName = server;
	this->port = port;
}


TCPClient::~TCPClient() {
	if (this->__isConnected == true) {
		disconnect();
	}
}


int TCPClient::connect() {
	this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketfd < 0) {
		perror("TCPClient: error opening socket");
		return -1;
	}

	this->server = gethostbyname(this->serverName.c_str());
	if (this->server == NULL) {
		perror("TCPClient: no such host");
		return -1;
	}

	memset(&this->serverAddress, 0, sizeof(this->serverAddress));
	this->serverAddress.sin_family = AF_INET;

	memcpy(&this->serverAddress.sin_addr.s_addr, this->server->h_addr, 
			this->server->h_length);
	this->serverAddress.sin_port = htons(this->port);

	if (::connect(this->socketfd, (struct sockaddr*)&this->serverAddress,
					sizeof(this->serverAddress)) < 0) {
		perror("TCPClient: error connecting to the server");
		return -1;
	}

	this->__isConnected = true;
	return 0;
}


int TCPClient::connect(string server, int port) {
	this->serverName = server;
	this->port = port;

	return connect();
}


int TCPClient::disconnect() {
	this->__isConnected = false;
	::close(this->socketfd);
	return 0;
}


bool TCPClient::isConnected() {
	return this->__isConnected;
}


int TCPClient::send(string message) {
	const char* buffer = message.c_str();

	int n = ::write(this->socketfd, buffer, message.length());
	if (n < 0) {
       perror("TCPClient: error writing to socket");
       return -1;
    }
    return 0;
}


int TCPClient::receive(string& msg, uint16_t size){
    char buffer[size];
    int n = read(this->socketfd, buffer, size);
    if (n < 0) {
       perror("TCPClient: error reading from socket");
       return -1;
    }

    msg = string(buffer);
    return 0;
}

}