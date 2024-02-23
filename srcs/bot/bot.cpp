/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:14:01 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/23 12:47:07 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

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
	std::memset(buffer, 0, BUFFER_SIZE);
	ssize_t bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
 	if (bytesReceived == -1 || std::strstr(buffer, "End of NAMES list") == NULL)
		return (false);
	welcomeMessageSerious(channel);			//pick one of the two
	//welcomeMessageFunny(channel);			//pick one of the two
	std::string message = "PRIVMSG " + channel + " :Hi guys, type \"Hey Botijo\" to interact with me\r\n";
	send(clientSocket, message.c_str(), message.size(), 0);
	return (true);
}

int main(int argc, char **argv)
{
	if (argc != 5 || std::atoi(argv[2]) < 1 || std::atoi(argv[2]) > 65535)
		return errorMessage("Please introduce valid arguments as shown below.\n./bot <host> <port> <password> <channel>");		
	std::string password = argv[3];
	std::string channel = "#" + std::string(argv[4]);
	std::string botNick = "Botijo";
	std::signal(SIGINT, cleanExit);

	struct addrinfo hints, *res;
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;						// Allow IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(argv[1], argv[2], &hints, &res) != 0)
		return errorMessage("Unable to resolve hostname.");
	int clientSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (clientSocket == -1)
	{
		freeaddrinfo(res);
		return errorMessage("Unable to create socket.");
	}
	if (connect(clientSocket, res->ai_addr, res->ai_addrlen) == -1)
	{
		freeaddrinfo(res);
		return errorMessage("Unable to connect to server.");
	}
	freeaddrinfo(res);
	if (!registration(clientSocket, password, botNick, channel))
		return errorMessage("Unable to register the connection with server and join the channel.");
	while (1);
}

// g++ -Wall -Wextra -Werror -std=c++98 -pedantic bot.cpp -o bot && ./bot localhost 6667 1234 channel
// ideas: hacer un "make bot" dentro del makefile
//        saludo al unirse al canal
