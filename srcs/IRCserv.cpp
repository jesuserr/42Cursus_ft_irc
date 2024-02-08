/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:10:24 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/08 18:29:13 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

void welcomeMessage(int port)
{
	system("clear");
	std::cout << "  _                                         \n"
				" (_)                                        \n"
				"  _ _ __ ___   ___  ___ _ ____   _____ _ __ \n"
				" | | '__/ __| / __|/ _ \\ '__\\ \\ / / _ \\ '__|\n"
				" | | | | (__  \\__ \\  __/ |   \\ V /  __/ |   \n"
				" |_|_|  \\___| |___/\\___|_|    \\_/ \\___|_|\n";
	std::cout << "   by Carlos Escañuela & Jesús Serrano\n";
	std::cout << "\n   Server listening through port: " << port << "\n\n";
}

int main(int argc, char **argv)
{
	IRCErrorLog _error;
	mapClients _clients;	// mapClients is equivalent to std::map<int, IRCClient>
	if (argc != 3)
		return _error.Error("Use me with port number and password. Example: ircserv 6667 password.");
	else if (std::atoi(argv[1]) < 1 || std::atoi(argv[1]) > 65535)
		return _error.Error("The port has to be a number between 1 and 65535.");
	IRCSocket _socket(std::atoi(argv[1]), &_error);
	IRCCore _irc(argv[2], _clients);
	if (!_socket.IRClisten())
		return (1);
	welcomeMessage(std::atoi(argv[1]));	
	while (_socket.IRCPoll(_clients))
		_irc.run();
	return (0);	
}
