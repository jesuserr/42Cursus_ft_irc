/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:34:14 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/21 10:57:22 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
# define IRCCLIENT_HPP

# include "IRCIncludes.hpp"

class IRCClient
{
	private:
		std::string _in;
		std::string _out;
		bool 		_clientAuthenticated;
		std::string _nickname;
		std::string _username;
		bool		_clientRegistered;		
		std::string _realname;
		std::string _flags;

	public:
		IRCClient();
		~IRCClient();
		
		/***************************** GETTERS ********************************/
		bool getClientAuthentication() const;
		std::string getNickname() const;
		std::string getUsername() const;
		bool getClientRegistration() const;
		std::string getRealname() const;
		std::string getFlags(void) const;
				
		/***************************** SETTERS ********************************/
		void setClientAuthentication(bool status);
		void setNickname(std::string nickname);
		void setUsername(std::string username);
		void setClientRegistration(bool status);
		void setRealname(std::string realname);

		/***************************** FUNCTIONS ******************************/
		std::string &Getin();
		std::string &Getout();
		void SendIRCMsg(std::string msg);
		bool setFlag(char flag);
		bool removeFlag(char flag);
		bool checkFlag(char flag);		
};

#endif
