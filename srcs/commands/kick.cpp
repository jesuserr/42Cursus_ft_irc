/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:06:07 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#kick-message

#include "../../incs/IRCIncludes.hpp"

bool kickParsing(std::string parameters, std::string *parsedParameters)
{
	std::stringstream ss(parameters);
	std::getline(ss, parsedParameters[0], ' ');
	std::getline(ss, parsedParameters[1], ' ');
	std::getline(ss, parsedParameters[2], '\0');
	if (parsedParameters[1].empty())
		return (false);
	if (!parsedParameters[2].empty() && (parsedParameters[2].find(":") == std::string::npos))
		return (false);
	if ((parsedParameters[0].find(":") != std::string::npos) || \
	(parsedParameters[1].find(":") != std::string::npos))
		return (false);
	parsedParameters[2].erase(0, 1);
	if ((parsedParameters[0].find_first_not_of(VALID_CHANNEL_CHARSET) != std::string::npos))
		return (false);
	if ((parsedParameters[1].find_first_not_of(VALID_USER_CHARSET) != std::string::npos))
		return (false);
	if (parsedParameters[2].empty())
	{
		parsedParameters[2] = "Kicked out by operator. Consider it as a warning.";
		parsedParameters[2] += " Repeated behavior will result in a ban.";
	}
	return (true);
}

void IRCCore::kick(IRCClient &client, std::string parameters)
{
	std::string parsedParameters[3];
	for (int i = 0; i < 3; i++)
		parsedParameters[i].clear();
	if (kickParsing(removeTabsAndMultipleSpaces(parameters), parsedParameters))
	{
		std::string channel = parsedParameters[0];
		std::string user = parsedParameters[1];
		std::string message = parsedParameters[2];
		mapChannelList::iterator itc = _channels.find(channel);
		if (itc != _channels.end())								 // Checks if channel exists
		{
			if (itc->second.checkUser(client.getNickname()))	 // Checks if client is in the channel
			{
				if (itc->second.checkOper(client.getNickname())) // Checks if client is operator
				{
					if (itc->second.checkUser(user))			 // Checks if user is in the channel
					{
						std::string userId = USER_ID(client.getNickname(), client.getUsername());
						itc->second.sendMsg(client, RPL_KICKCHANNEL(userId, channel, user, message), true);
						itc->second.delUser(user);
						if (itc->second.getUsers().size() == 0)
							_channels.erase(channel);
					}
					else
						client.SendIRCMsg(ERR_USERNOTINCHANNEL(client.getNickname(), user, channel));
				}
				else
				client.SendIRCMsg(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel));
			}
			else
				client.SendIRCMsg(ERR_NOTONCHANNEL(client.getNickname(), channel));
		}
		else
			client.SendIRCMsg(ERR_NOSUCHCHANNEL(client.getNickname(), channel));
	}
	else
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "KICK"));
}
