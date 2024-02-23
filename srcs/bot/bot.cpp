/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:14:01 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/23 17:27:18 by jesuserr         ###   ########.fr       */
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
	//welcomeMessageSerious(channel);
	welcomeMessageFunny(channel);
	std::string message = "PRIVMSG " + channel + " :Hi guys, type \"Hey Botijo\" to start interacting with me\r\n";
	send(clientSocket, message.c_str(), message.size(), 0);
	return (true);
}

int connection(char **argv)
{
	struct addrinfo hints, *res;
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
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
	return (clientSocket);
}

int readMessage(int clientSocket, std::string &msg)
{
	char buffer[BUFFER_SIZE];
	std::memset(buffer, 0, BUFFER_SIZE);
	ssize_t bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
	if (bytesReceived == -1)
		return errorMessage("Unable to receive data from server.\n");
	else if (bytesReceived == 0)
		return errorMessage("Connection closed by server.\n");
	std::stringstream ss(buffer);
	std::getline(ss, msg, ':');
	std::getline(ss, msg, ':');	
	std::getline(ss, msg, '\r');
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 5 || std::atoi(argv[2]) < 1 || std::atoi(argv[2]) > 65535)
		return errorMessage("Please introduce valid arguments as shown below.\n./ircbot <host> <port> <password> <channel>");		
	std::string password = argv[3];
	std::string channel = "#" + std::string(argv[4]);
	std::string botNick = "Botijo";
	std::signal(SIGINT, cleanExit);
	
	int clientSocket = connection(argv);
	if (clientSocket == 1)
		return (1);
	if (!registration(clientSocket, password, botNick, channel))
		return errorMessage("Unable to register the connection with server and join the channel.");
	std::string msg;
	while (1)
	{
		if (readMessage(clientSocket, msg) == 1)
			return (1);
		if (msg.find("Hey Botijo") != std::string::npos && msg.size() == 10)
			sendMessage(clientSocket, channel, "Hi, what can I do for you? Remember to start your message with \"Botijo\"");
		else if (msg.find("Botijo") != std::string::npos && msg.size() == 6)
			sendMessage(clientSocket, channel, "Yes, yes, that's my name, don't wear it out");
		else if (msg.find("Botijo") != std::string::npos && ((msg.find("time") != std::string::npos) || (msg.find("date") != std::string::npos)))
			sendMessage(clientSocket, channel, "You are in a computer, have you considered to take a look to the screen corner?");
		else if (msg.find("Botijo") != std::string::npos && (msg.find("weather") != std::string::npos))
			sendMessage(clientSocket, channel, "Take a look through the window, it will be faster");
		else if (msg.find("Botijo") != std::string::npos && msg.find("ñ") != std::string::npos)
			sendMessage(clientSocket, channel, "Mi no hablar españolo");
		else if (msg.find("Botijo") != std::string::npos && msg.find("?") != std::string::npos)
			sendMessage(clientSocket, channel, "Always asking things... please be a little bit more proactive");
		else if (msg.find("Botijo") != std::string::npos && msg.find("!") != std::string::npos)
			sendMessage(clientSocket, channel, "Chill, no need to yell at me, it's hard to be a troll bot, you know?");
		else
			sendMessage(clientSocket, channel, "Unfortunately, I have no answer to all your questions, have you heard about something called Google?");
	}
}
