/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCoreCommandsUtils.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:35:23 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/11 14:08:48 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

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
