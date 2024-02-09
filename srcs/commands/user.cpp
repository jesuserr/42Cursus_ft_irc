/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:44:02 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/09 12:28:14 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#user-message

#include "../IRCIncludes.hpp"

std::string removeTabsAndMultipleSpaces(std::string line)
{
	std::replace(line.begin(), line.end(), '\t', ' ');
	std::string result;
	char lastChar = 0;
	for (std::string::iterator it = line.begin(); it != line.end(); ++it)
	{
		if (!(*it == ' ' && lastChar == ' '))
		{
			result += *it;
			lastChar = *it;
		}
	}
	return (result);
}

bool parsing(std::string parameters, std::string *parsedParameters)
{
	std::string cleanParameters = removeTabsAndMultipleSpaces(parameters);	
	std::stringstream ss(cleanParameters);
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

void IRCCore::user(IRCClient &client, std::string parameters, std::string serverTime)
{
	if (!client.getClientAuthentication() || client.getNickname().empty())
		return;
	if (client.getClientRegistration())
 	{
		client.SendIRCMsg(ERR_ALREADYREGISTERED(client.getUsername()));
		return;
	}
	std::string parsedParameters[4];
	for (int i = 0; i < 4; i++)
		parsedParameters[i].clear();
	if (parsing(parameters, parsedParameters))
	{
		client.setUsername(parsedParameters[0]);
		client.setRealname(parsedParameters[3]);
		client.setClientRegistration(true);
		std::string userId = USER_ID(client.getNickname(), client.getUsername());
		client.SendIRCMsg(RPL_WELCOME(client.getNickname(), userId));
		client.SendIRCMsg(RPL_YOURHOST(client.getUsername(), SERVER_NAME, SERVER_VERSION));		   
		client.SendIRCMsg(RPL_CREATED(client.getUsername(), serverTime));
	}
	else
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "USER"));	
}
