/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modechannel.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:14:49 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/IRCIncludes.hpp"

void IRCCore::mode(IRCClient &client, std::string parameters)
{
	std::string channel;
	std::string flags;
	
	parameters = trim(parameters);
	if (!parameters.empty())
	{	
		if (parameters.find(" ") != std::string::npos)
		{
			channel = parameters.substr(0, parameters.find(" "));
			parameters.erase(0,parameters.find(" ") + 1);
		}
		else
		{
			channel = parameters;
			parameters.clear();
		}
	}
	else
	{
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "MODE"));
		return;
	}
	if (!channel.empty() && channel.at(0) != '#' && channel.at(0) != '@')
	{
		modeUser(client, channel, parameters);
		return;
	}
	if (channel.empty() || (channel.at(0) != '#' && channel.at(0) != '@') || _channels.find(channel) == _channels.end())
	{
		client.SendIRCMsg(ERR_NOSUCHCHANNEL(client.getNickname(), channel));
		return;
	}
	if (parameters.empty())
	{
		client.SendIRCMsg(RPL_CHANNELMODEISBYSERVER(client.getNickname(), channel, _channels.find(channel)->second.getFlags(), ""));
		return;
	}
	if (!_channels.find(channel)->second.checkOper(client.getNickname()))
	{
		client.SendIRCMsg(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel));
		return;
	}
	if (parameters.size() == 1 || parameters.at(1) == ' ' || (parameters.at(0) != '+' && parameters.at(0) != '-') || (parameters.find("+") != std::string::npos && parameters.find("-") != std::string::npos))
	{
		client.SendIRCMsg(ERR_BADCHANMASK(channel));
		return;
	}
	if (parameters.find(" ") != std::string::npos)
	{
		flags = parameters.substr(0, parameters.find(" "));
		parameters.erase(0, parameters.find(" "));
		parameters = trim(parameters);
	}
	else
	{
		flags = parameters;
		parameters.clear();
	}
	if (flags.at(0) == '+')
	{
		flags.erase(0, 1);
		while (!flags.empty())
		{
			if (std::tolower(flags.at(0)) == 'o')
				modePlusO(client, channel, parameters);
			else if (std::tolower(flags.at(0)) == 'k')
				modePlusK(client, channel, parameters);
			else if (std::tolower(flags.at(0)) == 't')
				modePlusT(client, channel);
			else if (std::tolower(flags.at(0)) == 'l')
				modePlusL(client, channel, parameters);
			else if (std::tolower(flags.at(0)) == 'i')
				modePlusI(client, channel);
			else 
				client.SendIRCMsg(ERR_UNKNOWNMODE(client.getNickname(), flags.substr(0, 1), channel));
			flags.erase(0, 1);
		}
	}
	else 
	{
		flags.erase(0, 1);
		while (!flags.empty())
		{
			if (std::tolower(flags.at(0)) == 'o')
				modeMinusO(client, channel, parameters);
			else if (std::tolower(flags.at(0)) == 'k')
				modeMinusK(client, channel, parameters);
			else if (std::tolower(flags.at(0)) == 't')
				modeMinusT(client, channel);
			else if (std::tolower(flags.at(0)) == 'l')
				modeMinusL(client, channel);
			else if (std::tolower(flags.at(0)) == 'i')
				modeMinusI(client, channel);
			else 
				client.SendIRCMsg(ERR_UNKNOWNMODE(client.getNickname(), flags.substr(0, 1), channel));
			flags.erase(0, 1);
		}
	}
}

void IRCCore::modePlusT(IRCClient &client, std::string channel)
{
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	_channels.find(channel)->second.setFlag('t');
	_channels.find(channel)->second.sendMsg(client, RPL_CHANNELMODEIS(userId, channel, "+t", ""));
}

void IRCCore::modeMinusT(IRCClient &client, std::string channel)
{
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	_channels.find(channel)->second.removeFlag('t');
	_channels.find(channel)->second.sendMsg(client, RPL_CHANNELMODEIS(userId, channel, "-t", ""));
}

void IRCCore::modePlusO(IRCClient &client, std::string channel, std::string parameters)
{
	if (parameters.empty())
	{
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "MODE +o"));
		return;
	}
	if (!_channels.find(channel)->second.checkUser(parameters))
	{
		client.SendIRCMsg(ERR_USERNOTINCHANNEL(client.getUsername(), parameters, channel));
		return;
	}
	_channels.find(channel)->second.addOper(parameters);
	_channels.find(channel)->second.sendMsg(client, RPL_CHANNELMODEIS(USER_ID(client.getNickname(), client.getUsername()), channel, "+o", parameters));
}

void IRCCore::modeMinusO(IRCClient &client, std::string channel, std::string parameters)
{
	if (parameters.empty())
	{
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "MODE +o"));
		return;
	}
	if (!checkUser(parameters))
	{
		client.SendIRCMsg(ERR_NOSUCHNICK(client.getUsername(), parameters));
		return;
	}
	if (!_channels.find(channel)->second.checkOper(parameters))
	{
		client.SendIRCMsg(ERR_USERNOTINCHANNEL(client.getUsername(), parameters, channel));
		return;
	}
	_channels.find(channel)->second.delOper(parameters);
	_channels.find(channel)->second.sendMsg(client, RPL_CHANNELMODEIS(USER_ID(client.getNickname(), client.getUsername()), channel, "-o", parameters));
}

void IRCCore::modePlusK(IRCClient &client, std::string channel, std::string parameters)
{
	if (parameters.empty())
	{
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "MODE +k"));
		return;
	}
	_channels.find(channel)->second.setFlag('k');
	_channels.find(channel)->second.setKey(parameters);
	_channels.find(channel)->second.sendMsg(client, RPL_CHANNELMODEIS(USER_ID(client.getNickname(), client.getUsername()), channel, "+k", parameters));	
}

void IRCCore::modeMinusK(IRCClient &client, std::string channel, std::string parameters)
{
	(void)parameters;
	(void)client;
	_channels.find(channel)->second.removeFlag('k');
	_channels.find(channel)->second.setKey("");
	_channels.find(channel)->second.sendMsg(client, RPL_CHANNELMODEIS(USER_ID(client.getNickname(), client.getUsername()), channel, "-k", ""));	
}

void IRCCore::modePlusL(IRCClient &client, std::string channel, std::string parameters)
{
	if (parameters.empty() || std::atoi(parameters.c_str()) == 0 || \
	std::atoi(parameters.c_str()) > MAX_USERS_PER_CHANNEL)
	{
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getNickname(), "MODE +l"));
		return;
	}
	mapChannelList::iterator it = _channels.find(channel);
	it->second.setFlag('l');
	it->second.setMaxUsers(std::atoi(parameters.c_str()));
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	it->second.sendMsg(client, RPL_CHANNELMODEIS(userId, channel, "+l", parameters));
}

void IRCCore::modeMinusL(IRCClient &client, std::string channel)
{
	mapChannelList::iterator it = _channels.find(channel);
	it->second.removeFlag('l');
	it->second.setMaxUsers(MAX_USERS_PER_CHANNEL);	
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	it->second.sendMsg(client, RPL_CHANNELMODEIS(userId, channel, "-l", ""));
}

void IRCCore::modePlusI(IRCClient &client, std::string channel)
{
	mapChannelList::iterator it = _channels.find(channel);
	it->second.setFlag('i');
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	it->second.sendMsg(client, RPL_CHANNELMODEIS(userId, channel, "+i", ""));
}

void IRCCore::modeMinusI(IRCClient &client, std::string channel)
{
	mapChannelList::iterator it = _channels.find(channel);
	it->second.removeFlag('i');
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	it->second.sendMsg(client, RPL_CHANNELMODEIS(userId, channel, "-i", ""));
}
