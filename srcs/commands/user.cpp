/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:44:02 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#user-message

#include "../../incs/IRCIncludes.hpp"

bool userParsing(std::string parameters, std::string *parsedParameters)
{
	std::stringstream ss(parameters);
	std::getline(ss, parsedParameters[0], ' ');
	std::getline(ss, parsedParameters[1], ' ');
	std::getline(ss, parsedParameters[2], ' ');
	std::getline(ss, parsedParameters[3], '\0');
	for (int i = 0; i < 4; i++)
	{
		if (parsedParameters[i].empty())
			return (false);
		if (i < 3 && parsedParameters[i].find(":") != std::string::npos)
			return (false);
		if (i == 3 && parsedParameters[i].find(":") == std::string::npos)
			return (false);
	}
	parsedParameters[3].erase(0, 1);
	for (int i = 0; i < 4; i++)
		if ((parsedParameters[i].find_first_not_of(VALID_USER_CHARSET) != std::string::npos))
			return (false);
	return (true);
}

void IRCCore::user(IRCClient &client, std::string parameters)
{
	if (!client.getClientAuthentication())
		return;
	if (client.getClientRegistration())
 	{
		client.SendIRCMsg(ERR_ALREADYREGISTERED(client.getUsername()));
		return;
	}
	std::string parsedParameters[4];
	for (int i = 0; i < 4; i++)
		parsedParameters[i].clear();
	if (userParsing(removeTabsAndMultipleSpaces(parameters), parsedParameters))
	{
		client.setUsername(parsedParameters[0]);
		client.setRealname(parsedParameters[3]);
		if (!client.getNickname().empty())
		{
			client.setClientRegistration(true);
			welcomeMessages(client);
		}
	}
	else
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "USER"));	
}
