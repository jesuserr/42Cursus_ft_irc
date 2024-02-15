/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:14:49 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/15 12:07:51 by cescanue         ###   ########.fr       */
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
			else if (std::tolower(flags.at(0)) == 'i')
				modePlusi(client, channel, parameters);
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
			else if (std::tolower(flags.at(0)) == 'i')
				modeMinusi(client, channel, parameters);
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
	(void) client;
	std::cout << "mode +o channel:" << channel << " parameters:" << parameters << std::endl;
	
}

void IRCCore::modePlusi(IRCClient &client, std::string channel, std::string parameters)
{
	(void) client;
	std::cout << "mode +i channel:" << channel << " parameters:" << parameters << std::endl;
	
}

void IRCCore::modeMinuso(IRCClient &client, std::string channel, std::string parameters)
{
	(void) client;
	std::cout << "mode -o channel:" << channel << " parameters:" << parameters << std::endl;
	
}

void IRCCore::modeMinusi(IRCClient &client, std::string channel, std::string parameters)
{
	(void) client;
	std::cout << "mode -i channel:" << channel << " parameters:" << parameters << std::endl;
	
}


