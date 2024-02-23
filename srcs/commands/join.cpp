/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:57:22 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/23 21:29:08 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/IRCIncludes.hpp"

void IRCCore::join(IRCClient &client, std::string parameters)
{
	std::string channels, keys;
	parameters = trim(parameters);
	if (parameters.empty())
	{
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getNickname(), "JOIN"));
		return;
	}
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
		channels = trim(channels);
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

bool IRCCore::checkChannelFull(IRCClient &client, std::string channel)
{
	mapChannelList::iterator it = _channels.find(channel);
	
	if (it != _channels.end() && it->second.getUsers().size() >= it->second.getMaxUsers())
	{
		client.SendIRCMsg(ERR_CHANNELISFULL(client.getNickname(), channel));
		return true;
	}
	return false;
}

bool IRCCore::checkInvitationList(IRCClient &client, std::string channel)
{
	mapChannelList::iterator it = _channels.find(channel);
	
	if (it == _channels.end())
		return true;
	if (!it->second.checkFlag('i'))
		return true;
	if (it->second.checkInvited(client.getNickname()))
	{
		it->second.delInvited(client.getNickname());
		return true;
	}
	client.SendIRCMsg(ERR_INVITEONLYCHAN(client.getNickname(), channel));
	return false;
}

void IRCCore::joinc(IRCClient &client, std::string channel, std::string key)
{
	
	channel = trim(channel);
	if (channel.empty())
	{
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getNickname(), "JOIN"));
		return;
	}
	if (!channel.empty() && channel.at(0) != '#' && channel.at(0) != '@')
	{
		client.SendIRCMsg(ERR_NOSUCHCHANNEL(client.getNickname(), channel));
		return;
	}
	if (channel.find_first_not_of(VALID_CHANNEL_CHARSET) != std::string::npos)
	{
		client.SendIRCMsg(ERR_NOSUCHNICK(client.getUsername(), channel));
		return;
	}
	if (checkChannelFull(client, channel))
		return;
	if (!checkInvitationList(client, channel))
		return;
	mapChannelList::iterator it = _channels.find(channel);
	if (it != _channels.end())
	{
		if (it->second.getKey().empty() || it->second.getKey() == key)
			it->second.addUser(client.getNickname());
		else
		{
			client.SendIRCMsg(ERR_BADCHANNELKEY(client.getNickname(), channel));
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
	it = _channels.find(channel);
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	it->second.sendMsg(client, RPL_JOINCHANNEL(userId, channel));
	if (!it->second.getTopic().empty())
		client.SendIRCMsg(RPL_TOPIC(client.getNickname(), channel, it->second.getTopic()));
	client.SendIRCMsg(RPL_NAMREPLY(channel, client.getNickname(), _channels.find(channel)->second.getListUsers()));
	client.SendIRCMsg(RPL_ENDOFNAMES(channel, client.getNickname()));
}	
