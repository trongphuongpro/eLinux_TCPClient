/**
 * @file tcpclient.cpp
 * @brief Wrapper class for Client-side of TCP/IPv4 socket connection.
 * @author Nguyen Trong Phuong
 * @date 2020 Jan 28
 */


#include "tcpclient.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>


using namespace std;

namespace eLinux {

TCPClient::TCPClient() {
	this->socketfd = -1;
	this->__isConnected = false;
}


TCPClient::TCPClient(string server, int port) {
	this->socketfd = -1;
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
	struct sockaddr_in server;
	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_NUMERICSERV;

	/**
	 * Get server's info
	 */
	if (getaddrinfo(this->serverName.c_str(),
					to_string(this->port).c_str(),
					&hints, &result) != 0) {
		perror("TCPClient: no such host");
		return -1;
	}

	freeaddrinfo(result);

	this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->socketfd < 0) {
		perror("TCPClient: error opening socket");
		return -1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(this->port);

	if (inet_pton(AF_INET, this->serverName.c_str(), &server.sin_addr) <= 0) {
		perror("TCPClient: Failed for parsing server address");
		return -1;
	}

	if (::connect(this->socketfd, (struct sockaddr*)&server,
					sizeof(struct sockaddr_in)) < 0) {
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


void TCPClient::disconnect() {
	this->__isConnected = false;
	::close(this->socketfd);
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
    return n;
}


int TCPClient::receive(string& msg, uint16_t size){
    char buffer[size];
    int n = read(this->socketfd, buffer, size);
    if (n < 0) {
       perror("TCPClient: error reading from socket");
       return -1;
    }

    msg = string(buffer);
    return n;
}

} /* namespace eLinux */