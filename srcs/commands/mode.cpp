/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:14:49 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/14 11:47:29 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IRCIncludes.hpp"

void IRCCore::mode(IRCClient &client, std::string parameters)
{
	std::string channel;
	std::string flags;
	
	if (parameters.find(" ") != std::string::npos && !parameters.substr(parameters.find(" ") + 1, parameters.size()).empty())
	{	
		channel = parameters.substr(0, parameters.find(" "));
		parameters.erase(0,parameters.find(" ") + 1);
		parameters = trim(parameters);
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
	if (!_channels.find(channel)->second.checkOper(client.getNickname()))
	{
		client.SendIRCMsg(ERR_CHANOPRIVSNEEDED(channel));
		return;
	}
	if (parameters.size() == 1 || parameters.at(1) == ' ' || (parameters.at(0) != '+' && parameters.at(0) != '-'))
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
			if (flags.at(0) == 'o')
				modePluso(client, channel, parameters);
			else if (flags.at(0) == 'i')
				modePlusi(client, channel, parameters);
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
			if (flags.at(0) == 'o')
				modeMinuso(client, channel, parameters);
			else if (flags.at(0) == 'i')
				modeMinusi(client, channel, parameters);
			else 
				client.SendIRCMsg(ERR_UNKNOWNMODE(flags.substr(0, 1), channel));
			flags.erase(0, 1);
		}
	}
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


