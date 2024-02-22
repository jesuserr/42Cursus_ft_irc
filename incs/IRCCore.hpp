/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:58:31 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/21 09:41:05 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCORE_HPP
# define IRCCORE_HPP

# include "IRCIncludes.hpp"

class IRCCore
{
	private:
		IRCCore();
		IRCCore(IRCCore const &cpy);
		IRCCore &operator=(IRCCore const &rhs);
		
		mapClients 			&_clients;
		vectorChannelUsers 	&_usersdisconnected;
		mapChannelList 		_channels;
		std::string 		_password;
		std::string 		_startingTime;
		
		void quitDisconnectedUsers(void); 		// Calls QUIT when user loses connection
		bool checkUser(std::string nickname); 	// Checks if user exists at server level
		void command(IRCClient &client, std::string cmd, std::string param);
				
		/**************************** COMMANDS ********************************/
		void pass(IRCClient &client, std::string input, std::string password);
		void nick(IRCClient &client, std::string newNick);
		void user(IRCClient &client, std::string parameters);
		void ping(IRCClient &client, std::string token);
		void join(IRCClient &client, std::string parameters);
		void privmsg(IRCClient &client, std::string parameters);
		void part(IRCClient &client, std::string parameters);
		void quit(IRCClient &client, std::string message);
		void topic(IRCClient &client, std::string message);
		void kick(IRCClient &client, std::string parameters);
		void whois(IRCClient &client, std::string parameters);
		void list(IRCClient &client, std::string parameters);
		void invite(IRCClient &client, std::string parameters);
		void mode(IRCClient &client, std::string parameters);
		
		/****************** COMMANDS Auxiliary Functions **********************/
		// For JOIN
		void joinc(IRCClient &client, std::string channel, std::string key);
		bool checkChannelFull(IRCClient &client, std::string channel);
		bool checkInvitationList(IRCClient &client, std::string channel);
		// For Channel MODE
 		void modePlusO(IRCClient &client, std::string channel, std::string parameter);
		void modeMinusO(IRCClient &client, std::string channel, std::string parameter);
		void modePlusK(IRCClient &client, std::string channel, std::string parameter);
		void modeMinusK(IRCClient &client, std::string channel, std::string parameter);
		void modePlusT(IRCClient &client, std::string channel);
		void modeMinusT(IRCClient &client, std::string channel);
		void modePlusL(IRCClient &client, std::string channel, std::string parameter);
		void modeMinusL(IRCClient &client, std::string channel);
		void modePlusI(IRCClient &client, std::string channel);
		void modeMinusI(IRCClient &client, std::string channel);
		// For User MODE
		void modeUser(IRCClient &client, std::string user, std::string flags);
		void modeUserPlusI(IRCClient &client);
		void modeUserMinusI(IRCClient &client);
		
		/********************* IRCCoreCommandsUtils.cpp ***********************/
		std::string obtainStartingTime(void);
		void welcomeMessages(IRCClient &client);
		std::string removeTabsAndMultipleSpaces(std::string line);
		std::string trim(const std::string& str);
		void uppercaseCommand(std::string &cmd);
		
	public:	
		IRCCore(std::string pass, mapClients &clients, vectorChannelUsers &usersdisconnected);
		void run(void);
};

#endif
