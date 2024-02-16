/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:06:56 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/16 16:20:49 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IRCIncludes.hpp"

void IRCCore::topic(IRCClient &client, std::string parameters)
{
	std::string channel;
	
	if (parameters.empty())
	{
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "TOPIC"));
		return;
	}
	if (parameters.find(" ") != std::string::npos)
	{
		channel = parameters.substr(0, parameters.find(" "));
		parameters = parameters.substr(parameters.find(" "), parameters.size());
		parameters = trim(parameters);
	}
	else
	{
		channel = trim(parameters);
		parameters.clear();
	}
	if (_channels.find(channel) == _channels.end())
	{
		client.SendIRCMsg(ERR_NOSUCHCHANNEL(channel));
		return;
	}
	if (!_channels.find(channel)->second.checkUser(client.getNickname()))
	{
		client.SendIRCMsg(ERR_NOTONCHANNEL(client.getNickname(), channel));
		return;
	}
	if (parameters.empty())
	{
		if (!_channels.find(channel)->second.getTopic().empty())
		{
			client.SendIRCMsg(RPL_TOPIC(client.getNickname(), channel, _channels.find(channel)->second.getTopic()));
			std::string userId = USER_ID(client.getNickname(), client.getUsername());
			client.SendIRCMsg(RPL_TOPICWHOTIME(client.getNickname(), channel, userId, _channels.find(channel)->second.getTopicTime()));
			return;	
		}
		else
		{
			client.SendIRCMsg(RPL_NOTOPIC(channel));
			return;
		}
	}
	else
	{
		if (_channels.find(channel)->second.checkFlag('t') && !_channels.find(channel)->second.checkOper(client.getNickname()))
		{
			client.SendIRCMsg(ERR_CHANOPRIVSNEEDED(channel));
			return;
		}
		else
		{	
			if (parameters[0] == ':')
				parameters.erase(0, 1);
			_channels.find(channel)->second.setTopic(parameters);
			std::time_t result = std::time(nullptr);
    		_channels.find(channel)->second.setTopicTime(std::ctime(&result));
			std::string userId = USER_ID(client.getNickname(), client.getUsername());
			_channels.find(channel)->second.sendMsg(client, RPL_TOPICSET(userId, channel, parameters));
		}
	}
}

