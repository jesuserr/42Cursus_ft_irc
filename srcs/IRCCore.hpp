/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:43:30 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/09 21:44:44 by cescanue         ###   ########.fr       */
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
		std::string obtainStartingTime(void);
		
		/**************************** COMMANDS ********************************/
		void pass(IRCClient &client, std::string input, std::string password);
		void nick(IRCClient &client, std::string newNick);
		void user(IRCClient &client, std::string parameters, std::string serverTime);
		void ping(IRCClient &client, std::string token);
	
	public:	
		IRCCore(std::string pass, mapClients &clients);
		void run(void);
		void Command(IRCClient &client, std::string cmd, std::string param);
};

#endif
