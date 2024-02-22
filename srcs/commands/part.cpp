/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:28:38 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#part-message

#include "../../incs/IRCIncludes.hpp"

bool partParsing(std::string parameters, std::string *channel, std::string *message)
{
	std::stringstream ss(parameters);
	std::getline(ss, *channel, ' ');
	std::getline(ss, *message, '\0');
	if (channel->empty() || (!message->empty() && (*message)[0] != ':') || \
	(channel->find_first_not_of(VALID_CHANNEL_CHARSET) != std::string::npos))
		return (false);
	return (true);
}

void IRCCore::part(IRCClient &client, std::string parameters)
{
	std::string channel;
	std::string message;
	
	if (partParsing(removeTabsAndMultipleSpaces(parameters), &channel, &message))
	{
		mapChannelList::iterator itc = _channels.find(channel);
		if (itc != _channels.end())
		{			
			if (itc->second.checkUser(client.getNickname()))
			{
				std::string userId = USER_ID(client.getNickname(), client.getUsername());
				itc->second.sendMsg(client, RPL_PARTCHANNEL(userId, channel, message), true);
				itc->second.delUser(client.getNickname());
				if (itc->second.getUsers().size() == 0)
					_channels.erase(channel);
			}
			else
				client.SendIRCMsg(ERR_NOTONCHANNEL(client.getNickname(), channel));
		}
		else
			client.SendIRCMsg(ERR_NOSUCHCHANNEL(client.getNickname(), channel));
	}
	else
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "PART"));
}
