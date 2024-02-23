/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:14:01 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/23 01:07:35 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <iostream>
#include <arpa/inet.h>
#define BUFFER_SIZE	8192

void welcomeMessage(std::string channel)
{
	system("clear");
	std::cout << "\033[?25l";
	std::cout << "     _            _           _   \n"
				"    (_)          | |         | |  \n"
				"     _ _ __ ___  | |__   ___ | |_ \n"
				"    | | '__/ __| | '_ \\ / _ \\| __|		\n"
				"    | | | | (__  | |_) | (_) | |_		\n"
				"    |_|_|  \\___| |_.__/ \\___/ \\__|	\n";
	std::cout << "  by Carlos Escañuela & Jesús Serrano\n";
	std::cout << "\n Bot connected to server on channel: " << channel << "\n\n";
}

int errorMessage(std::string message)
{
	std::cerr << message << std::endl;
	return (1);	
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
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	ssize_t bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
 	if (bytesReceived == -1 || std::strstr(buffer, "End of NAMES list") == NULL)
		return (false);
	welcomeMessage(channel);
	return (true);
}

int main(int argc, char **argv)
{
	if (argc != 5 || std::atoi(argv[2]) < 1 || std::atoi(argv[2]) > 65535) //add more checks?
		return errorMessage("Please introduce valid arguments as shown below\n./bot localhost 6667 <password> <channel>");
			
	std::string server = argv[1];
	int port = std::atoi(argv[2]);
	std::string password = argv[3];
	std::string channel = "#" + std::string(argv[4]);
	std::string botNick = "Botijo";

	int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == -1)
		return errorMessage("Unable to create socket.");
		
	sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");			//Cambiar esto, puede ser otra ip
	if (connect(clientSocket, (sockaddr*)&address, sizeof(address)) == -1)
		return errorMessage("Unable to connect to server.");	
		
	if (!registration(clientSocket, password, botNick, channel))
		return errorMessage("Unable to register the connection with server and join the channel.");
	
	while (1);	
}

// g++ -Wall -Wextra -Werror -std=c++98 -pedantic bot.cpp -o bot && ./bot localhost 6667 1234 channel
// ideas: hacer un "make bot" dentro del makefile
//        saludo al unirse al canal
