/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:04:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/20 19:06:16 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#invite-message

#include "../IRCIncludes.hpp"

bool inviteParsing(std::string parameters, std::string *channel, std::string *message)
{
	std::stringstream ss(parameters);
	std::getline(ss, *channel, ' ');
	std::getline(ss, *message, '\0');
	if (channel->empty() || (!message->empty() && (*message)[0] != ':') || \
	(channel->find_first_not_of(VALID_CHANNEL_CHARSET) != std::string::npos))
		return (false);
	return (true);
}

void IRCCore::invite(IRCClient &client, std::string parameters)
{
	std::string channel;
	std::string message;
	
	if (inviteParsing(removeTabsAndMultipleSpaces(parameters), &channel, &message))
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
