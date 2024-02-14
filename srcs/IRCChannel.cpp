/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:18:21 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/14 16:39:50 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

IRCChannel::~IRCChannel()
{
}

IRCChannel::IRCChannel(std::string name, mapClients &clients) : _clients(clients)
{
	_name = name;
	_topicRestriction = false;
	
}

bool IRCChannel::addUser(std::string user)
{
	if (std::find(_users.begin(), _users.end(), user) == _users.end())
	{
		_users.push_back(user);
		return true;
	}
	return false;
}

bool IRCChannel::delUser(std::string user)
{
	vectorChannelUsers::iterator it;
	
	it = std::find(_users.begin(), _users.end(), user);
	if (it != _users.end())
	{
		delOper(user);
		_users.erase(it);
		return true;
	}
	return false;
}

bool IRCChannel::addOper(std::string oper)
{
	if (std::find(_operators.begin(), _operators.end(), oper) == _operators.end())
	{
		_operators.push_back(oper);
		return true;
	}
	return false;
}

bool IRCChannel::delOper(std::string oper)
{
	vectorChannelUsers::iterator it;
	
	it = std::find(_operators.begin(), _operators.end(), oper);
	if (it != _operators.end())
	{
		_operators.erase(it);
		return true;
	}
	return false;
}

void IRCChannel::setKey(std::string key)
{
	_key = key;
}

std::string IRCChannel::getKey(void)
{
	return _key;
}

void IRCChannel::setTopic(std::string topic)
{
	_topic = topic;
}

std::string IRCChannel::getTopic(void)
{
	return _topic;
}

vectorChannelUsers IRCChannel::getUsers(void)
{
	return _users;
}

vectorChannelUsers IRCChannel::getOpers(void)
{
	return _operators;
}

std::string IRCChannel::getListUsers(void)
{
	std::string users;
	vectorChannelUsers::iterator it = _operators.begin();
	while (it != _operators.end())
	{
		users += "@";
		users += *it;
		users += " ";
		it++;
	}
	it = _users.begin();
	while (it != _users.end())
	{
		if (std::find(_operators.begin(), _operators.end(), *it) == _operators.end())
		{
			users += *it;
			users += " ";
		}
		it++;
	}
	return users;
}

void IRCChannel::sendMsg(IRCClient &client, std::string msg, bool sendtome)
{
	for (vectorChannelUsers::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (*it != client.getNickname() || sendtome == true)
			for (mapClients::iterator itc = _clients.begin(); itc != _clients.end() ; itc++)
			{
				if (itc->second.getNickname() == *it)
					itc->second.SendIRCMsg(msg);
			}
	}
}

bool IRCChannel::checkOper(std::string oper)
{
	if (std::find(_operators.begin(), _operators.end(), oper) != _operators.end())
		return true;
	return false;
}

bool IRCChannel::checkUser(std::string user)
{
	if (std::find(_users.begin(), _users.end(), user) != _users.end())
		return true;
	return false;
}

void IRCChannel::setTopicRestriction(bool mode)
{
	_topicRestriction = mode;
}

