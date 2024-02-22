/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:32:58 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#privmsg-message

#include "../../incs/IRCIncludes.hpp"

bool privmsgParsing(std::string parameters, std::string *target, std::string *message)
{
	std::stringstream ss(parameters);
	std::getline(ss, *target, ' ');
	std::getline(ss, *message, '\0');
	if (target->empty() || message->empty() || (*message)[0] != ':' || \
	(target->find_first_not_of(VALID_CHANNEL_CHARSET) != std::string::npos))
		return (false);
	return (true);
}

void IRCCore::privmsg(IRCClient &client, std::string parameters)
{
	std::string target;
	std::string message;	
	if (privmsgParsing(removeTabsAndMultipleSpaces(parameters), &target, &message))
	{
		if (!target.empty() && (target.at(0) == '#' || target.at(0) == '@') && _channels.find(target) != _channels.end())
		{
			mapChannelList::iterator itc = _channels.find(target);
			vectorChannelUsers users = itc->second.getUsers();
			if (std::find(users.begin(), users.end(), client.getNickname()) != users.end())
			{
				std::string userId = USER_ID(client.getNickname(), client.getUsername());
				itc->second.sendMsg(client, RPL_PRIVMSGCHANNEL(userId, target, message), false);
			}
			else 
				client.SendIRCMsg(ERR_CANNOTSENDTOCHAN(client.getNickname(), target));
			return;
		}
		for (mapClients::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			if (it->second.getNickname() == target)
			{
				std::string userId = USER_ID(client.getNickname(), client.getUsername());
				it->second.SendIRCMsg(RPL_PRIVMSG(userId, target, message));
				return;
			}			
		}
		client.SendIRCMsg(ERR_NOSUCHNICK(client.getUsername(), target));
	}
	else if (target.empty() || parameters.empty())
		client.SendIRCMsg(ERR_NORECIPIENT(client.getUsername()));
	else if (message.empty() || message[0] != ':')
		client.SendIRCMsg(ERR_NOTEXTTOSEND(client.getUsername()));
	else if ((target.find_first_not_of(VALID_USER_CHARSET) != std::string::npos))
		client.SendIRCMsg(ERR_NOSUCHNICK(client.getUsername(), target));
}
