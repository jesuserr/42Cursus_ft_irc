#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>

#define PORT	6667

int main()
{
	// 56.2 Creating a Socket: socket()
	// int socket(int domain, int type, int protocol);
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
	{
		std::cerr << "Unable to create socket.\n";
		return (-1);
	}
	std::cout << "Socket created successfully.\n";

	// 56.5.3 Connecting to a Peer Socket: connect()
	// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	int connecting = connect(clientSocket, (sockaddr*)&address, sizeof(address));
	if (connecting == -1)
	{
		std::cerr << "Unable to connect to server.\n";
		return (-1);
	}
	std::cout << "Connected to server through port: " << PORT << "\n";

	// 61.3 Socket-Specific I/O System Calls: recv() and send()
	// ssize_t send(int sockfd, const void *buffer, size_t length, int flags);	
 	std::string userInput;
	size_t		bytesSent;
	do
	{
		userInput.clear();
		if (!std::getline(std::cin, userInput))
			return (-1);
		bytesSent = send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);		
	} 
	while (bytesSent);	
	return (0);
}

// g++ -Wall -Wextra -Werror -std=c++98 -pedantic client.cpp && ./a.out
// nc localhost 6667