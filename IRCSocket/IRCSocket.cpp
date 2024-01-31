/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:53:30 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/31 22:36:40 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCSocket.hpp"

IRCSocket::~IRCSocket()
{
	return ;
}

IRCSocket::IRCSocket(int port, IRCErrorLog *log)
{
	_log = log;
	_listenPort = port;
	_listening = false;
	_nfds = 0;
}

bool IRCSocket::IRClisten(void)
{
	struct sockaddr_in6  iaddr;
	int on = 1;
	
	_listen_sd = socket (AF_INET6, SOCK_STREAM, 0);
	if (_listen_sd < 0)
		return _log->Error("It has not been able to create the main listening socket.");
	if (setsockopt(_listen_sd, SOL_SOCKET,  SO_REUSEADDR,
                  (char *)&on, sizeof(on)) < 0)
		return _log->Error("Impossible to set the main socket as reusable.");
	if (fcntl(_listen_sd, F_SETFL, O_NONBLOCK) < 0)
		return _log->Error("Unable to set the main socket as non-blocking.");
	memset(&iaddr, 0, sizeof(iaddr));
	iaddr.sin6_family = AF_INET6;
	memcpy(&iaddr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	iaddr.sin6_port = htons(_listenPort);
	if (bind(_listen_sd, (struct sockaddr *)&iaddr, sizeof(iaddr)) < 0)
		return _log->Error("Unable to bind the socket to the available local IPs.");
	if (listen(_listen_sd, MAXLISTENQUEUE) < 0)
		return _log->Error("Unable to listen to the socket on the specified port.");
	_fds[0].fd = _listen_sd;
	_fds[0].events = POLLIN;
	_nfds = 1;
	_listening = true;
	return true;
}

bool IRCSocket::IRCPoll(std::map<int, s_socketdata> &mapdata)
{
	char buffer[500];
	int rc;
	bool compressfds = false;
	
	if (!_listening)
		return _log->Error("You have not set listening mode.");
	if (poll(_fds, _nfds, -1) < 0)
		return _log->Error("Unable to poll the connections.");
	int new_sd = 1;
	int currentsize = _nfds;
	while (_fds[0].revents != 0 && new_sd != -1)
	{
		new_sd = accept(_listen_sd, NULL, NULL);
		if (new_sd < 0 && errno != EWOULDBLOCK)
			return _log->Error("Unable to create a socket for a new connection");
		_fds[_nfds].fd = new_sd;
		_fds[_nfds].events = POLLIN;
		_nfds++;
	}
	for (int c = 1; c < currentsize ; c++)
	{
		if(_fds[c].revents == 0)
       		continue;
		while ((rc = recv(_fds[c].fd, buffer, sizeof(buffer), 0)) > 0)
			mapdata[c].in.insert(mapdata[c].in.size(), buffer, rc);
		if (rc < 0 && errno != EWOULDBLOCK)
			return _log->Error("A problem occurred while receiving data");
		if (rc == 0)
		{
			//Aqui nunca entra se tiene que revisar
			std::cout << "here";
			close(_fds[c].fd);
          	_fds[c].fd = -1;
			compressfds = true;
			if (mapdata.find(c) != mapdata.end())
				mapdata.erase(mapdata.find(c));
		}
	}
	if (compressfds)
	{
		compressfds = false;
		for (int i = 0; i < _nfds; i++)
		{
			if (_fds[i].fd == -1)
			{
				for(int j = i; j < _nfds-1; j++)
				{
					_fds[j].fd = _fds[j+1].fd;
				}
				i--;
				_nfds--;
			}
		}
	}
	return true;
}