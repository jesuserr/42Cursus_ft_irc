/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:14:47 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/11 13:44:24 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#nick-message

#include "../IRCIncludes.hpp"

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
		std::string userId = USER_ID(client.getNickname(), client.getUsername());
		client.SendIRCMsg(RPL_NICK(userId, newNick));
		client.setNickname(newNick);
		if (!client.getRealname().empty())
		{
			client.setClientRegistration(true);
			welcomeMessages(client);
		}
	}
}
