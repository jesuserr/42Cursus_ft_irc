#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fcntl.h>

#define BUFFER_SIZE	8192
#define PORT		6667

int main()
{
	// 56.2 Creating a Socket: socket()
	// int socket(int domain, int type, int protocol);
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
	{
		std::cerr << "Unable to create socket.\n";
		return (-1);
	}
	std::cout << "Socket created successfully.\n";

	// 61.9 Socket Options
	// int setsockopt(int sockfd, int level, int optname, const void *optval,
	// socklen_t optlen);
	int optval = 1;
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
	{
		std::cerr << "Unable to set socket as reusable.\n";
		return (-1);
	}
	std::cout << "Socket set as reusable.\n";

	// Set socket to be nonblocking.
  	if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
	{
		std::cerr << "Unable to set socket as nonblocking.\n";
		return (-1);
	}
	std::cout << "Socket set as nonblocking.\n";

	// 56.3 Binding a Socket to an Address: bind()
	// int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);	
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	int binding = bind(serverSocket, (sockaddr*)&address, sizeof(address));
	if (binding == -1)
	{
		std::cerr << "Unable to bind socket to address.\n";
		return (-1);
	}
	std::cout << "Socket bound successfully.\n";

	// 56.5.1 Listening for Incoming Connections: listen()
	// int listen(int sockfd, int backlog);
	int listening = listen(serverSocket, SOMAXCONN);
	if (listening == -1)
	{
		std::cerr << "Unable to set socket in listening mode.\n";
		return (-1);
	}
	std::cout << "Socket in listening mode through port: " << PORT << "\n";

	// 63.2.1 The select() System Call
	// int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
	// struct timeval *timeout);
	fd_set currentSockets, readySockets;
	FD_ZERO(&currentSockets);
	FD_SET(serverSocket, &currentSockets);
	while(true)
	{
		readySockets = currentSockets;
		if (select(FD_SETSIZE, &readySockets, NULL, NULL, NULL) < 0)
		{
			std::cerr << "Select was not able to read from socket.\n";
			return (-1);
		}
		for (int fd = 0; fd < FD_SETSIZE; fd++)
		{
			if (FD_ISSET(fd, &readySockets))
			{
				if (fd == serverSocket)						// New connection
				{
					sockaddr_in	client;
					socklen_t	clientSize = sizeof(client);
					int clientSocket = accept(serverSocket, (sockaddr*)&client, &clientSize);
					if (clientSocket == -1)
					{
						std::cerr << "Error connecting to client.\n";
						return (-1);
					}
					std::cout << "New client " << clientSocket << " connected.\n";					
					FD_SET(clientSocket, &currentSockets);
				}
				else										// New message
				{
					char buffer[BUFFER_SIZE];
					memset(buffer, 0, BUFFER_SIZE);
					int bytesReceived = recv(fd, buffer, BUFFER_SIZE, 0);
					if (bytesReceived <= 0)
					{
						close(fd);
						std::cout << "Client disconnected.\n";
						FD_CLR(fd, &currentSockets);
					}
					else
					{
						std::cout << "message->" << std::string(buffer, 0, bytesReceived);
						if (buffer[bytesReceived - 1] != '\n')
							std::cout << std::endl;						
					}					
				}
			}
		}
	}
}
