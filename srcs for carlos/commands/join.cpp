/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:57:22 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/12 23:06:37 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IRCIncludes.hpp"

void IRCCore::join(IRCClient &client, std::string parameters)
{
	if (!client.getClientRegistration())
	{
		client.SendIRCMsg(ERR_NOTREGISTERED());
		return;
	}
	std::string channels, keys;
	if (parameters.find(" ") != std::string::npos)
	{
		channels = parameters.substr(0, parameters.find(" "));
		parameters.erase(0, parameters.find(" ") + 1);
		keys = parameters;
	}
	else
		channels = parameters;
	while (channels.find(",") != std::string::npos)	
	{
		std::string c;
		std::string k;
		
		c = channels.substr(0, channels.find(","));
		channels.erase(0, channels.find(",") + 1);
		if (keys.find(",") != std::string::npos)
		{
			k = keys.substr(0, keys.find(","));
			keys.erase(0, keys.find(",") + 1);
		}
		else if (keys.empty())
		{
			k = keys;
			keys.clear();
		}
		joinc(client, c, k);
	}
		joinc(client, channels, keys);
}

void IRCCore::joinc(IRCClient &client, std::string channel, std::string key)
{
	if (channel.at(0) != '#' && channel.at(0) != '@')
	{
		client.SendIRCMsg(ERR_NOSUCHCHANNEL(channel));
		return;
	}
	mapChannelList::iterator it = _channels.find(channel);
	if (it != _channels.end())
	{
		if (it->second.getKey().empty() || it->second.getKey() == key)
			it->second.addUser(client.getNickname());
		else
		{
			client.SendIRCMsg(ERR_BADCHANNELKEY(channel));
			return;
		}
	}
	else
	{
		IRCChannel t(channel, _clients);
		t.addUser(client.getNickname());
		t.addOper(client.getNickname());
		t.setKey(key);
		_channels.insert(std::pair<std::string, IRCChannel>(channel, t));
	}
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	std::cout << "Aqui";
	client.SendIRCMsg(RPL_JOINCHANNEL(userId, channel));
	if (!it->second.getTopic().empty())
		client.SendIRCMsg(RPL_TOPIC(channel, "it->second.getTopic()"));
	client.SendIRCMsg(RPL_NAMREPLY(channel, client.getNickname(), _channels.find(channel)->second.getListUsers()));
	client.SendIRCMsg(RPL_ENDOFNAMES(channel, client.getNickname()));
}	