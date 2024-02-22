/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:11:46 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#quit-message

#include "../../incs/IRCIncludes.hpp"

void IRCCore::quit(IRCClient &client, std::string message)
{
	bool messagePrinted = false;
	
	if ((!message.empty() && message[0] == ':') || message.empty())
	{
		for (mapChannelList::iterator it = _channels.begin(); it != _channels.end();)
		{
			if (it->second.checkUser(client.getNickname()))
			{
				if (!messagePrinted)
				{
					std::string userId = USER_ID(client.getNickname(), client.getUsername());
					it->second.sendMsg(client, RPL_QUITCHANNEL(userId, message), false);
					messagePrinted = true;
				}
				it->second.delUser(client.getNickname());
				if (it->second.getUsers().size() == 0)
					_channels.erase(it++);
				else
					++it;
			}
			else
				++it;
		}
		for (mapClients::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			if (client.getClientAuthentication() && it->second.getNickname() == client.getNickname())
			{
				close(it->first);				
				break;
			}
		}
	}
	else
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "QUIT"));
}
