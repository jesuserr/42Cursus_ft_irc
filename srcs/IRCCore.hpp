/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:43:30 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/15 18:22:47 by jesuserr         ###   ########.fr       */
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
		void mode(IRCClient &client, std::string parameters);
		void modePluso(IRCClient &client, std::string channel, std::string parameter);
		void modeMinuso(IRCClient &client, std::string channel, std::string parameter);
		void modePlusi(IRCClient &client, std::string channel, std::string parameter);
		void modeMinusi(IRCClient &client, std::string channel, std::string parameter);
		void modePlust(IRCClient &client, std::string channel);
		void modeMinust(IRCClient &client, std::string channel);
		void part(IRCClient &client, std::string parameters);
		void quit(IRCClient &client, std::string message);

		/********************* IRCCoreCommandsUtils.cpp ***********************/
		std::string obtainStartingTime(void);
		void welcomeMessages(IRCClient &client);
		std::string removeTabsAndMultipleSpaces(std::string line);
		
	public:	
		IRCCore(std::string pass, mapClients &clients);
		void run(void);
		void Command(IRCClient &client, std::string cmd, std::string param);
};

#endif
