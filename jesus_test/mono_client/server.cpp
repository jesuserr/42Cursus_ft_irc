#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <string>

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

	// 56.5.2 Accepting a Connection: accept()
	// int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	sockaddr_in	client;
	socklen_t	clientSize = sizeof(client);
	int clientSocket = accept(serverSocket, (sockaddr*)&client, &clientSize);
	if (clientSocket == -1)
	{
		std::cerr << "Error connecting to client.\n";
		return (-1);
	}
	std::cout << "Client connected.\n";

	// 61.3 Socket-Specific I/O System Calls: recv() and send()
	// ssize_t recv(int sockfd, void *buffer, size_t length, int flags);
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	size_t bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
	while (bytesReceived)
	{
		std::cout << "message->" << std::string(buffer, 0, bytesReceived);
		if (buffer[bytesReceived - 1] != '\n')
			std::cout << std::endl;
		memset(buffer, 0, BUFFER_SIZE);
		bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
	}
	close(clientSocket);
	std::cout << "Client disconnected.\n";
	close(serverSocket);
	std::cout << "Server disconnected.\n";
	return (0);
}
