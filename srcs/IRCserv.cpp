/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:10:24 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/06 14:39:23 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include <map>
#include "IRCErrorLog.hpp"
#include "IRCSocket.hpp"
#include "IRCCore.hpp"
#include "IRCReplies.hpp"

void test_messages()
{
	std::string client = "client";
	std::string command = "command";
	std::string nick = "nick";
	std::string oldNick = "oldNick";
	std::string newNick = "newNick";
	std::cout << ERR_NEEDMOREPARAMS(client, command) << std::endl;
	std::cout << ERR_ALREADYREGISTERED(client) << std::endl;
	std::cout << ERR_PASSWDMISMATCH(client) << std::endl;
	std::cout << ERR_NONICKNAMEGIVEN(client) << std::endl;
	std::cout << ERR_ERRONEUSNICKNAME(client, nick) << std::endl;
	std::cout << ERR_NICKNAMEINUSE(client, nick) << std::endl;
	std::cout << RPL_NICK(oldNick, client, newNick) << std::endl;	
}

int main(int argc, char **argv)
{
	IRCErrorLog _error;
	std::map<int, IRCClient> _clients;
	if (argc != 3)
		return _error.Error("Use me with port number and password. Example: ircserv 6667 password.");
	else if (std::atoi(argv[1]) < 1 || std::atoi(argv[1]) > 65535)
		return _error.Error("The port has to be a number between 1 and 65535.");
	IRCSocket _socket(std::atoi(argv[1]), &_error);
	IRCCore _irc(argv[2], _clients);
	if (!_socket.IRClisten())
		return (1);
	test_messages();
	while (_socket.IRCPoll(_clients))
	{
		_irc.run();
		_socket.IRCSend(_clients);
	}
	return (0);	
}
