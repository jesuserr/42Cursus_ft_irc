/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:14:49 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/13 22:05:09 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IRCIncludes.hpp"

void IRCCore::mode(IRCClient &client, std::string parameters)
{
	std::string channel;
	if (parameters.find(" ") != std::string::npos)
	{	
		channel = parameters.substr(0, parameters.find(" "));
		parameters.erase(0,parameters.find(" ") + 1);
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
	
	
		
	std::cout << parameters << std::endl;
}


