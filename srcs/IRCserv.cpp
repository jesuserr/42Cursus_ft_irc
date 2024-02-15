/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:10:24 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/15 21:56:48 by cescanue         ###   ########.fr       */
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

void cleanexit(int signal)
{
	(void) signal;
	throw std::runtime_error("\b\b   Server disconnected - See you soon!\n");
}

int main(int argc, char **argv)
{
	IRCErrorLog _error;
	mapClients _clients;	// mapClients is equivalent to std::map<int, IRCClient>
	vectorChannelUsers _usersdisconnected;
	if (argc != 3)
		return _error.Error("Use me with port number and password. Example: ircserv 6667 password.");
	else if (std::atoi(argv[1]) < 1 || std::atoi(argv[1]) > 65535)
		return _error.Error("The port has to be a number between 1 and 65535.");
	std::signal(SIGINT, cleanexit);
	IRCSocket _socket(std::atoi(argv[1]), &_error);
	IRCCore _irc(argv[2], _clients, _usersdisconnected);
	if (_socket.IRClisten())
		return (1);
	welcomeMessage(std::atoi(argv[1]));	
	try
	{
		while (_socket.IRCPoll(_clients, _usersdisconnected))
		{
			std::cout << "number of clients: " << _clients.size() << std::endl;
			std::cout << "number of users lost: " << _usersdisconnected.size() << std::endl;
			for (int c = 0; c < (int) _usersdisconnected.size(); c++)
				std::cout << _usersdisconnected[c] << std::endl;
			
			_irc.run();
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		exit(0);
	}
	return (0);	
}
