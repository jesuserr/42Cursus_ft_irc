/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:18:21 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/12 14:15:36 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

IRCChannel::~IRCChannel()
{
}

IRCChannel::IRCChannel(std::string name)
{
	_name = name;
}

bool IRCChannel::addUser(std::string user)
{
	if (std::find(_users.begin(), _users.end(), user) == std::end(_users))
	{
		_users.push_back(user);
		return true;
	}
	return false;
}

bool IRCChannel::delUser(std::string user)
{
	mapChannelUsers::iterator it;
	
	it = std::find(_users.begin(), _users.end(), user);
	if (it != std::end(_users))
	{
		delOper(user);
		_users.erase(it);
		return true;
	}
	return false;
}

bool IRCChannel::addOper(std::string oper)
{
	if (std::find(_operators.begin(), _operators.end(), oper) == std::end(_operators))
	{
		_operators.push_back(oper);
		return true;
	}
	return false;
}

bool IRCChannel::delOper(std::string oper)
{
	mapChannelUsers::iterator it;
	
	it = std::find(_operators.begin(), _operators.end(), oper);
	if (it != std::end(_operators))
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

mapChannelUsers IRCChannel::getUsers(void)
{
	return _users;
}

mapChannelUsers IRCChannel::getOpers(void)
{
	return _operators;
}

std::string IRCChannel::getListUsers(void)
{
	std::string users;
	mapChannelUsers::iterator it = _operators.begin();
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
		if (std::find(_operators.begin(), _operators.end(), *it) == std::end(_operators))
		{
			users += *it;
			users += " ";
		}
		it++;
	}
	return users;
}
