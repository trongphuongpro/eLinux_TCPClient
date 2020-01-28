/**
 * @file tcpclient.h
 * @brief 
 * @author Nguyen Trong Phuong
 * @date 2020 Jan 28
 */

#ifndef __TCPCLIENT__
#define __TCPCLIENT__

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>

namespace eLinux {

class TCPClient {
public:

	TCPClient();
	TCPClient(std::string server, int port);
	~TCPClient();

	virtual int connect();
	virtual int connect(std::string server, int port);
	virtual int disconnect();
	virtual int send(std::string message);
	virtual int receive(std::string& message, uint16_t len=1024);

	virtual bool isConnected();

private:
	int socketfd;
	struct sockaddr_in serverAddress;
	struct hostent *server;
	std::string serverName;
	int port;
	bool __isConnected;
};

} /* namespace eLinux */

#endif /* __TCPCLIENT__ */