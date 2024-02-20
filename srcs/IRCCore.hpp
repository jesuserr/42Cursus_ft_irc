/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:34:58 by cescanue          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/02/20 11:30:25 by cescanue         ###   ########.fr       */
=======
/*   Updated: 2024/02/20 11:29:27 by jesuserr         ###   ########.fr       */
>>>>>>> cb10489a0a4e93c52ea9b200606ba82b6dd5fde3
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
		mapClients &_clients;
		vectorChannelUsers &_usersdisconnected;
		mapChannelList _channels;
		std::string _password;
		std::string trim(const std::string& str);
		std::string _startingTime;
		void uppercaseCommand(std::string &cmd);
				
		/**************************** COMMANDS ********************************/
		void pass(IRCClient &client, std::string input, std::string password);
		void nick(IRCClient &client, std::string newNick);
		void user(IRCClient &client, std::string parameters);
		void ping(IRCClient &client, std::string token);
		void join(IRCClient &client, std::string parameters);
		void joinc(IRCClient &client, std::string channel, std::string key);
		void privmsg(IRCClient &client, std::string parameters);
		void part(IRCClient &client, std::string parameters);
		void quit(IRCClient &client, std::string message);
		void topic(IRCClient &client, std::string message);
		void kick(IRCClient &client, std::string parameters);
		void whois(IRCClient &client, std::string parameters);
		void list(IRCClient &client, std::string parameters);
		
		//Channel Mode
		void mode(IRCClient &client, std::string parameters);
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
		//User Mode
		void modeUser(IRCClient &client, std::string user, std::string flags);
		void modeUserPlusI(IRCClient &client);
		void modeUserMinusI(IRCClient &client);
		
		//Function that makes a call to the quit command when a user loses the connection
		void quitDisconnectedUsers(void);

		/********************* IRCCoreCommandsUtils.cpp ***********************/
		std::string obtainStartingTime(void);
		void welcomeMessages(IRCClient &client);
		std::string removeTabsAndMultipleSpaces(std::string line);

		//Client Utils
		bool checkUser(std::string nickname);
		
		
	public:	
		IRCCore(std::string pass, mapClients &clients, vectorChannelUsers &usersdisconnected);
		void run(void);
		void Command(IRCClient &client, std::string cmd, std::string param);
};

#endif
