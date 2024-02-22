/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:14:01 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 21:24:37 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>

int errorMessage(std::string message)
{
	std::cerr << message << std::endl;
	return (1);	
}

bool verifyArguments(int argc, char **argv)
{
	// add more checks
	if (argc != 5 || std::atoi(argv[2]) < 1 || std::atoi(argv[2]) > 65535)	
	{
		std::cerr << "Please introduce valid arguments as shown below\n";
		std::cerr << "./bot localhost 6667 <password> <channel>\n";
		return (false);
	}
	return (true);
}

bool registration(int clientSocket, std::string password, std::string botNick, std::string channel)
{
	std::string pass = "PASS " + password + "\r\n";
	send(clientSocket, pass.c_str(), pass.size(), 0);
	std::string login = "USER " + botNick + " * * :" + botNick + "\r\n";
	send(clientSocket, login.c_str(), login.size(), 0);
	std::string nick = "NICK " + botNick + "\r\n";
	send(clientSocket, nick.c_str(), nick.size(), 0);
	std::string join = "JOIN " + channel + "\r\n";
	send(clientSocket, join.c_str(), join.size(), 0);
	return (true);
	//detectar que algo ha ido mal y devolver false
}

int main(int argc, char **argv)
{
	system("clear");
	if (!verifyArguments(argc, argv))
		return (1);
		
	std::string server = argv[1];
	int port = std::atoi(argv[2]);
	std::string password = argv[3];
	std::string channel = "#" + std::string(argv[4]);
	std::string botNick = "Botijo";		

	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
		return errorMessage("Unable to create socket.");	
	std::cout << "Socket created successfully.\n";
	
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");			//Cambiar esto, puede ser otra ip
	if (connect(clientSocket, (sockaddr*)&address, sizeof(address)) == -1)
		return errorMessage("Unable to connect to server.");	
	std::cout << "Bot connected to server through port: " << port << "\n";
	
	if (!registration(clientSocket, password, botNick, channel))
		return errorMessage("Unable to register the connection with server.");
		
	// 61.3 Socket-Specific I/O System Calls: recv() and send()
	// ssize_t send(int sockfd, const void *buffer, size_t length, int flags);	
 	std::string userInput;
	size_t		bytesSent;
	do
	{
		userInput.clear();
		if (!std::getline(std::cin, userInput))
			return (1);
		bytesSent = send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);		
	} 
	while (bytesSent);	
	return (0);
}

// g++ -Wall -Wextra -Werror -std=c++98 -pedantic bot.cpp -o bot && ./bot localhost 6667 1234 channel
