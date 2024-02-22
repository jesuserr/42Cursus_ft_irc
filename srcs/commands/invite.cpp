/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:04:44 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 12:07:36 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#invite-message

#include "../../incs/IRCIncludes.hpp"

bool inviteParsing(std::string parameters, std::string *nick, std::string *channel)
{
	std::stringstream ss(parameters);
	std::getline(ss, *nick, ' ');
	std::getline(ss, *channel, '\0');
	if (nick->empty() || channel->empty() || \
	(nick->find_first_not_of(VALID_NICK_CHARSET) != std::string::npos) || \
	(channel->find_first_not_of(VALID_CHANNEL_CHARSET) != std::string::npos))
		return (false);
	return (true);
}

void IRCCore::invite(IRCClient &client, std::string parameters)
{
	std::string nick;
	std::string channel;
	
 	if (!inviteParsing(removeTabsAndMultipleSpaces(parameters), &nick, &channel))
		return (client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "INVITE")));
	mapChannelList::iterator itc = _channels.find(channel);
	if (itc == _channels.end())
		return (client.SendIRCMsg(ERR_NOSUCHCHANNEL(client.getNickname(), channel)));
	if (!itc->second.checkUser(client.getNickname()))
		return (client.SendIRCMsg(ERR_NOTONCHANNEL(client.getNickname(), channel)));
	if (itc->second.checkFlag('i') && !itc->second.checkOper(client.getNickname()))
		return (client.SendIRCMsg(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel)));
	if (itc->second.checkUser(nick))
		return (client.SendIRCMsg(ERR_USERONCHANNEL(client.getNickname(), nick, channel)));
	if (!checkUser(nick))
		return (client.SendIRCMsg(ERR_NOSUCHNICK(client.getNickname(), nick)));
	client.SendIRCMsg(RPL_INVITING(client.getNickname(), nick, channel));
	for (mapClients::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->second.getNickname() == nick)
		{
			std::string userId = USER_ID(client.getNickname(), client.getUsername());
			it->second.SendIRCMsg(RPL_INVITE(userId, nick, channel));
		}			
	}
	itc->second.addInvited(nick);
}
