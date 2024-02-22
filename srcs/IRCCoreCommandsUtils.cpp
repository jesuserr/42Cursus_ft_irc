/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCoreCommandsUtils.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:35:23 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 12:07:07 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/IRCIncludes.hpp"

std::string IRCCore::obtainStartingTime(void)
{
	time_t		elapsed_time;
	struct tm	*time_info;
	char		time_stamp[20];

	elapsed_time = time(NULL);
	time_info = localtime(&elapsed_time);
	strftime(time_stamp, 20, "%Y-%m-%d %H:%M:%S", time_info);
	return (time_stamp);
}	

void IRCCore::welcomeMessages(IRCClient &client)
{
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	client.SendIRCMsg(RPL_WELCOME(client.getNickname(), userId));
	client.SendIRCMsg(RPL_YOURHOST(client.getUsername(), SERVER_NAME, SERVER_VERSION));		   
	client.SendIRCMsg(RPL_CREATED(client.getUsername(), _startingTime));
	client.SendIRCMsg(RPL_MYINFO(client.getUsername(), SERVER_NAME, SERVER_VERSION, \
		USER_MODES, CHANNEL_MODES, CHANNEL_MODES_WITH_PARAM));
	std::string supportedTokens = "NICKLEN=9";
	client.SendIRCMsg(RPL_ISUPPORT(client.getUsername(), supportedTokens));
	client.SendIRCMsg(RPL_MOTDSTART(client.getUsername(), SERVER_NAME));
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), "███▓▒░░   Welcome back to the 90's   ░░▒▓███"));	
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), "  _                                         "));
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), " (_)                                        "));
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), "  _ _ __ ___   ___  ___ _ ____   _____ _ __ "));
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), " | | '__/ __| / __|/ _ \\ '__\\ \\ / / _ \\ '__|"));
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), " | | | | (__  \\__ \\  __/ |   \\ V /  __/ |   "));
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), " |_|_|  \\___| |___/\\___|_|    \\_/ \\___|_|"));
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), "   by Carlos Escañuela & Jesús Serrano"));
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), " "));
	client.SendIRCMsg(RPL_MOTD(client.getUsername(), "███▓▒░░    Remember to have fun!!    ░░▒▓███"));
	client.SendIRCMsg(RPL_ENDOFMOTD(client.getUsername()));
}

std::string IRCCore::removeTabsAndMultipleSpaces(std::string line)
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

std::string IRCCore::trim(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first)
		return str;
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

void IRCCore::uppercaseCommand(std::string &cmd)
{
	if (!cmd.empty())
		for (std::string::iterator it = cmd.begin(); it != cmd.end(); ++it)
		    *it = std::toupper(*it);	
}
