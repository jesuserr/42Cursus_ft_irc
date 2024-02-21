/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:10:24 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/21 13:52:22 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

void welcomeMessage(int port)
{
	system("clear");
	std::cout << "\033[?25l";
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
	throw std::runtime_error("\b\b\r   Server disconnected - See you soon!\n");
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
	std::cout << "\r   Connected clients: " << _clients.size() << std::flush;
	try
	{
		while (_socket.IRCPoll(_clients, _usersdisconnected))
		{
			std::cout << "\r   Connected clients: " << _clients.size() << "    " << std::flush;
			_irc.run();
		}
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << '\n';
		std::cout << "\033[?25h";
		exit(0);
	}
	return (0);
}
