/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:14:47 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#nick-message

#include "../../incs/IRCIncludes.hpp"

bool nickAlreadyInUse(mapClients &_clients, std::string newNick)
{
	for (mapClients::iterator it = _clients.begin(); it != _clients.end(); it++)
	{
		if (it->second.getNickname() == newNick)
			return true;		
	}
	return false;
}

void IRCCore::nick(IRCClient &client, std::string newNick)
{
	bool userInChannel = false;
	
	if (!client.getClientAuthentication())
		return;
	if (newNick.empty())
		client.SendIRCMsg(ERR_NONICKNAMEGIVEN(client.getUsername()));
	else if ((newNick.find_first_not_of(VALID_NICK_CHARSET) != std::string::npos) \
	|| (newNick.size() > NICK_MAX_LENGTH))
		client.SendIRCMsg(ERR_ERRONEUSNICKNAME(client.getUsername(), newNick));
	else if (nickAlreadyInUse(_clients, newNick))
		client.SendIRCMsg(ERR_NICKNAMEINUSE(client.getUsername(), newNick));
	else if (newNick != client.getNickname())
	{
		for (mapChannelList::iterator it = _channels.begin(); it != _channels.end(); it++)
		{
			if (it->second.checkUser(client.getNickname()))
			{
				if (!userInChannel)
				{
					std::string userId = USER_ID(client.getNickname(), client.getUsername());
					it->second.sendMsg(client, RPL_NICK(userId, newNick), true);
					userInChannel = true;
				}
				it->second.changeUserName(client.getNickname(), newNick);
				it->second.changeOperatorName(client.getNickname(), newNick);
			}
		}
		if (!userInChannel)
		{
			std::string userId = USER_ID(client.getNickname(), client.getUsername());
			client.SendIRCMsg(RPL_NICK(userId, newNick));
		}
		client.setNickname(newNick);		
		if (!client.getRealname().empty() && !client.getClientRegistration())
		{
			client.setClientRegistration(true);
			welcomeMessages(client);
		}
	}
}
