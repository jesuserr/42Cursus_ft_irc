/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:11:46 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/15 18:39:17 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#quit-message

#include "../IRCIncludes.hpp"

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
				it->second.delOper(client.getNickname());
				if (it->second.getUsers().size() == 0)
					_channels.erase(it++);
				else
					++it;
			}
		}
		// this deletion provokes a segfault
		for (mapClients::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			if (it->second.getNickname() == client.getNickname())
			{
				_clients.erase(it);
				break;
			}		
		}
	}
	else
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "QUIT"));
}
