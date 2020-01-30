/**
 * @file tcpclient.h
 * @brief Wrapper class for Client-side of TCP/IPv4 socket connection.
 * @author Nguyen Trong Phuong
 * @date 2020 Jan 28
 */

#ifndef __TCPCLIENT__
#define __TCPCLIENT__

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>


/**
 * @brief namespace eLinux
 */
namespace eLinux {

/**
 * @brief Class TCPCLient used for creating TCP Client.
 */
class TCPClient {
public:

	/**
	 * @brief Constructor
	 *
	 * Default constructor.
	 */
	TCPClient();


	/**
	 * @brief Constructor
	 *
	 * @param server server's name or address.
	 * @param port serser's port.
	 */
	TCPClient(std::string server, int port);


	/**
	 * @brief Destructor
	 */
	~TCPClient();


	/**
	 * @brief connect to server.
	 * @return 0:success, -1:failed.
	 */
	virtual int connect();


	/**
	 * @brief connect to server.
	 * @param server server's name or address.
	 * @param port serser's port.
	 * @return 0:success, -1:failed.
	 */
	virtual int connect(std::string server, int port);


	/**
	 * @brief Disconnect from server.
	 * @return nothing.
	 */
	virtual void disconnect();


	/**
	 * @brief Send a message to server.
	 * @param [in] message message will be sent.
	 * @return 0:success, -1:failed.
	 */
	virtual int send(std::string message);


	/**
	 * @brief Receive a message from server.
	 * @param [out] message message will be sent.
	 * @param [in] len max length of received message.
	 * @return 0:success, -1:failed.
	 */
	virtual int receive(std::string& message, uint16_t len=1024);


	/**
	 * @brief Check if client is connected to server.
	 * @return true/false.
	 */
	virtual bool isConnected();

private:
	int socketfd;
	std::string serverName;
	int port;
	bool __isConnected;
};

} /* namespace eLinux */

#endif /* __TCPCLIENT__ */