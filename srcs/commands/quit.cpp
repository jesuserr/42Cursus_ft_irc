/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 23:07:01 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/15 23:10:50 by cescanue         ###   ########.fr       */
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
				it->second.delOper(client.getNickname());	// I think is not needed, ask
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
				//_clients.erase(it);		// this deletion provokes a segfault
				break;
			}
		}
	}
	else
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "QUIT"));
}
