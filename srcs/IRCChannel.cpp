/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:18:21 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/22 12:07:24 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/IRCIncludes.hpp"

IRCChannel::IRCChannel(std::string name, mapClients &clients) : _clients(clients)
{
	_name = name;
	_flags.clear();
	_maxUsers = MAX_USERS_PER_CHANNEL;
}

IRCChannel::~IRCChannel()
{
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

void IRCChannel::setTopicTime(std::string time)
{
	_topictimestamp = time;
}

std::string IRCChannel::getTopicTime(void)
{
	return _topictimestamp;
}

void IRCChannel::setTopicUser(std::string user)
{
	_topicuser = user;
}

std::string IRCChannel::getTopicUser(void)
{
	return _topicuser;
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

void IRCChannel::changeUserName(std::string oldName, std::string newName)
{
	vectorChannelUsers::iterator it;
	
	it = std::find(_users.begin(), _users.end(), oldName);
	if (it != _users.end())
		*it = newName;
}

void IRCChannel::changeOperatorName(std::string oldName, std::string newName)
{
	vectorChannelUsers::iterator it;
		
	it = std::find(_operators.begin(), _operators.end(), oldName);
	if (it != _operators.end())
		*it = newName;
}

bool IRCChannel::setFlag(char flag)
{
	if (checkFlag(flag))
		return true;
	_flags += std::tolower(flag);
	return true;
}

bool IRCChannel::removeFlag(char flag)
{
	flag = std::tolower(flag);
	if (_flags.find(flag) == std::string::npos)
		return false;
	_flags.erase(_flags.find(flag), 1);
	return true;
}

bool IRCChannel::checkFlag(char flag)
{
	if (_flags.find(std::tolower(flag)) != std::string::npos)
		return true;
	return false;	
}

std::string IRCChannel::getFlags(void)
{
	return _flags;
}

void IRCChannel::setMaxUsers(unsigned int max)
{
	_maxUsers = max;
}

unsigned int IRCChannel::getMaxUsers(void)
{
	return _maxUsers;
}

std::string IRCChannel::getName(void)
{
	return _name;
}

bool IRCChannel::addInvited(std::string user)
{
	if (std::find(_invited.begin(), _invited.end(), user) == _invited.end())
	{
		_invited.push_back(user);
		return true;
	}
	return false;
}

bool IRCChannel::delInvited(std::string user)
{
	vectorChannelUsers::iterator it;	
	it = std::find(_invited.begin(), _invited.end(), user);
	if (it != _invited.end())
	{
		_invited.erase(it);
		return true;
	}
	return false;
}

bool IRCChannel::checkInvited(std::string user)
{
	if (std::find(_invited.begin(), _invited.end(), user) != _invited.end())
		return true;
	return false;
}
