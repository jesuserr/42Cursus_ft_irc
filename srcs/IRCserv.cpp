/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:10:24 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/05 22:26:17 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cstdlib>
#include "IRCErrorLog.hpp"
#include "IRCSocket.hpp"
#include <map>

int main(int argc, char **argv)
{
	IRCErrorLog _error;
	std::map<int, IRCClient> _clients;
	if (argc != 3)
		return _error.Error("Use me with port number and password. Example: ircserv 6667 password.");
	else if (std::atoi(argv[1]) < 1 || std::atoi(argv[1]) > 65535)
		return _error.Error("The port has to be a number between 1 and 65535.");
	IRCSocket _socket(std::atoi(argv[1]), &_error);
	if (!_socket.IRClisten())
		return (1);
	while (_socket.IRCPoll(_clients))
	{
		for(std::map<int,IRCClient>::iterator it = _clients.begin(); it != _clients.end(); ++it) 
		{
			std::cout << it->second.Getin() << std::endl;
		}
	}
	return (0);	
}
