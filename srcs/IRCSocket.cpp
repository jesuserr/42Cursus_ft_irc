/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCSocket.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:53:30 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/25 20:52:23 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/IRCIncludes.hpp"

IRCSocket::~IRCSocket()
{
	for (int c = 0; c < _nfds ; c++)
		close(_fds[c].fd);
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
		return _log->Error("Unable to create main listening socket.");
	if (setsockopt(_fds[0].fd, SOL_SOCKET,  SO_REUSEADDR,
                  (char *)&on, sizeof(on)) < 0)
		return _log->Error("Unable to set main socket as reusable.");
	if (fcntl(_fds[0].fd, F_SETFL, O_NONBLOCK) < 0)
		return _log->Error("Unable to set main socket as non-blocking.");
	std::memset(&iaddr, 0, sizeof(iaddr));
	iaddr.sin6_family = AF_INET6;
	std::memcpy(&iaddr.sin6_addr, &in6addr_any, sizeof(in6addr_any));
	iaddr.sin6_port = htons(_listenPort);
	if (bind(_fds[0].fd, (struct sockaddr *)&iaddr, sizeof(iaddr)) < 0)
		return _log->Error("Unable to bind main socket to specified port.");
	if (listen(_fds[0].fd, MAXLISTENQUEUE) < 0)
		return _log->Error("Unable to set main socket in listening mode.");
	_fds[0].events = POLLIN;
	_nfds = 1;
	_listening = true;
	return false;
}

bool IRCSocket::IRCPoll(mapClients &mapdata, vectorChannelUsers &_usersdisconnected)
{
	char buffer[BUFFERSIZE];
	int rc;
	int currentsize;

	if (!_listening)
		return _log->Error("Socket not set in listening mode.");
	this->IRCSend(mapdata, _usersdisconnected);
	if (poll(_fds, _nfds, -1) < 0)
		return _log->Error("Unable to poll the connections.");
	int new_sd = accept(_fds[0].fd, NULL, NULL);
	while (_fds[0].revents != 0 && new_sd != -1)
	{
		if (new_sd < 0 && errno != EWOULDBLOCK)
			return _log->Error("Unable to create socket for new connection");
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
		while (_fds[c].fd > 0 && (rc = recv(_fds[c].fd, buffer, BUFFERSIZE, 0)) > 0)
			mapdata[_fds[c].fd].Getin().insert(mapdata[_fds[c].fd].Getin().size(), buffer, rc);
		if (rc < 0 && errno != EWOULDBLOCK)
		{
			deleteSDMAP(mapdata, c, _usersdisconnected);
			continue;
		}
		else if (rc == 0)
		{
			deleteSDMAP(mapdata, c, _usersdisconnected);
			continue;
		}
	}
	if (_compressfds)
		compressFDS();	
	return true;
}

void IRCSocket::deleteSDMAP(mapClients &mapdata, int c, vectorChannelUsers &_usersdisconnected)
{
	if (mapdata.find(_fds[c].fd) != mapdata.end())
	{
		if (!mapdata.find(_fds[c].fd)->second.getNickname().empty() &&std::find(_usersdisconnected.begin(), _usersdisconnected.end(), mapdata.find(_fds[c].fd)->second.getNickname()) == _usersdisconnected.end())
			_usersdisconnected.insert(_usersdisconnected.end(), mapdata.find(_fds[c].fd)->second.getNickname() + ":" + mapdata.find(_fds[c].fd)->second.getUsername());	
		mapdata.erase(mapdata.find(_fds[c].fd));
	}
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

bool IRCSocket::IRCSend(mapClients &mapdata, vectorChannelUsers &_usersdisconnected)
{
	int sd;
	int currentsize = _nfds;
	
	for (int c = 1; c < currentsize ; c++)
	{
		while (_fds[c].fd > 0 && mapdata[_fds[c].fd].Getout().size())
		{
			sd = send(_fds[c].fd, mapdata[_fds[c].fd].Getout().c_str(), mapdata[_fds[c].fd].Getout().size(), 0);
			if (sd < 0)
			{
				deleteSDMAP(mapdata, c, _usersdisconnected);
				continue;
			}
			else 
				mapdata[_fds[c].fd].Getout().erase(0, sd);
		}
	}
	return true;
}
