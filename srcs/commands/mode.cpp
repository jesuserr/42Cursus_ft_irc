/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:14:49 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/19 12:57:52 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IRCIncludes.hpp"

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
	if (channel.empty() ||  (channel.at(0) != '#' && channel.at(0) != '@') || _channels.find(channel) == _channels.end())
	{
		client.SendIRCMsg(ERR_NOSUCHCHANNEL(channel));
		return;
	}
	if (parameters.empty())
	{
		client.SendIRCMsg(RPL_CHANNELMODEISBYSERVER(channel, _channels.find(channel)->second.getFlags(), ""));
		return;
	}
	if (!_channels.find(channel)->second.checkOper(client.getNickname()))
	{
		client.SendIRCMsg(ERR_CHANOPRIVSNEEDED(channel));
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
				modePluso(client, channel, parameters);
			else if (std::tolower(flags.at(0)) == 'k')
				modePlusk(client, channel, parameters);
			else if (std::tolower(flags.at(0)) == 't')
				modePlust(client, channel);
			else 
				client.SendIRCMsg(ERR_UNKNOWNMODE(flags.substr(0, 1), channel));
			flags.erase(0, 1);
		}
	}
	else 
	{
		flags.erase(0, 1);
		while (!flags.empty())
		{
			if (std::tolower(flags.at(0)) == 'o')
				modeMinuso(client, channel, parameters);
			else if (std::tolower(flags.at(0)) == 'k')
				modeMinusk(client, channel, parameters);
			else if (std::tolower(flags.at(0)) == 't')
				modeMinust(client, channel);
			else 
				client.SendIRCMsg(ERR_UNKNOWNMODE(flags.substr(0, 1), channel));
			flags.erase(0, 1);
		}
	}
}

void IRCCore::modePlust(IRCClient &client, std::string channel)
{
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	_channels.find(channel)->second.setFlag('t');
	_channels.find(channel)->second.sendMsg(client, RPL_CHANNELMODEIS(userId, channel, "+t", ""));
}

void IRCCore::modeMinust(IRCClient &client, std::string channel)
{
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	_channels.find(channel)->second.removeFlag('t');
	_channels.find(channel)->second.sendMsg(client, RPL_CHANNELMODEIS(userId, channel, "-t", ""));
}

void IRCCore::modePluso(IRCClient &client, std::string channel, std::string parameters)
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



void IRCCore::modeMinuso(IRCClient &client, std::string channel, std::string parameters)
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

void IRCCore::modePlusk(IRCClient &client, std::string channel, std::string parameters)
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

void IRCCore::modeMinusk(IRCClient &client, std::string channel, std::string parameters)
{
	(void)parameters;
	(void)client;
	_channels.find(channel)->second.removeFlag('k');
	_channels.find(channel)->second.setKey("");
	_channels.find(channel)->second.sendMsg(client, RPL_CHANNELMODEIS(USER_ID(client.getNickname(), client.getUsername()), channel, "-k", ""));	
}


