/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:53:30 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/02 09:38:13 by cescanue         ###   ########.fr       */
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
	
	_fds[0].fd = socket (AF_INET6, SOCK_STREAM, 0);
	if (_fds[0].fd < 0)
		return _log->Error("It has not been able to create the main listening socket.");
	if (setsockopt(_fds[0].fd, SOL_SOCKET,  SO_REUSEADDR,
                  (char *)&on, sizeof(on)) < 0)
		return _log->Error("Impossible to set the main socket as reusable.");
	if (fcntl(_fds[0].fd, F_SETFL, O_NONBLOCK) < 0)
		return _log->Error("Unable to set the main socket as non-blocking.");
	memset(&iaddr, 0, sizeof(iaddr));
	iaddr.sin6_family = AF_INET6;
	memcpy(&iaddr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	iaddr.sin6_port = htons(_listenPort);
	if (bind(_fds[0].fd, (struct sockaddr *)&iaddr, sizeof(iaddr)) < 0)
		return _log->Error("Unable to bind the socket to the available local IPs.");
	if (listen(_fds[0].fd, MAXLISTENQUEUE) < 0)
		return _log->Error("Unable to listen to the socket on the specified port.");
	_fds[0].events = POLLIN;
	_nfds = 1;
	_listening = true;
	return true;
}

bool IRCSocket::IRCPoll(std::map<int, s_socketdata> &mapdata)
{
	char buffer[BUFFERSIZE];
	int rc;
	int sd;
	int currentsize;

	if (!_listening)
		return _log->Error("You have not set listening mode.");
	if (poll(_fds, _nfds, -1) < 0)
		return _log->Error("Unable to poll the connections.");
	int new_sd = accept(_fds[0].fd, NULL, NULL);
	while (_fds[0].revents != 0 && new_sd != -1)
	{
		if (new_sd < 0 && errno != EWOULDBLOCK)
			return _log->Error("Unable to create a socket for a new connection");
		_fds[_nfds].fd = new_sd;
		_fds[_nfds].events = POLLIN;
		_nfds++;
		new_sd = accept(_fds[0].fd, NULL, NULL);
	}
	currentsize = _nfds;
	_compressfds = false;
	for (int c = 1; c < currentsize ; c++)
	{
		if(_fds[c].revents == 0)
       		continue;
		while (_fds[c].fd > 0 && (rc = recv(_fds[c].fd, buffer, sizeof(buffer), 0)) > 0)
			mapdata[_fds[c].fd].in.insert(mapdata[_fds[c].fd].in.size(), buffer, rc);
		if (rc < 0 && errno != EWOULDBLOCK)
		{
			deleteSDMAP(mapdata, c);
			continue;
		}
		else if (rc == 0)
		{
			deleteSDMAP(mapdata, c);
			continue;
		}
		else
			while (_fds[c].fd > 0 && mapdata[_fds[c].fd].out.size())
			{
				sd = send(_fds[c].fd, mapdata[_fds[c].fd].out.c_str(), mapdata[_fds[c].fd].out.size(), 0);
				if (sd < 0)
				{
					deleteSDMAP(mapdata, c);
					continue;
				}
				else 
					mapdata[_fds[c].fd].out.erase(0, sd);
			}
	}
	if (_compressfds)
		compressFDS();	
	return true;
}

void IRCSocket::deleteSDMAP(std::map<int, s_socketdata> &mapdata, int c)
{
	if (mapdata.find(_fds[c].fd) != mapdata.end())
		mapdata.erase(mapdata.find(_fds[c].fd));
	close(_fds[c].fd);
	_fds[c].fd = -1;
	_compressfds = true;
}

void IRCSocket::compressFDS(void)
{
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
	_compressfds = false;
}
