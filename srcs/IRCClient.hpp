/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:34:14 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/08 17:03:39 by jesuserr         ###   ########.fr       */
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

	public:
		IRCClient();
		~IRCClient();
		std::string &Getin();
		std::string &Getout();
		void SendIRCMsg(std::string msg);
		
		/* GETTERS */
		bool getClientAuthentication() const;
		std::string getNickname() const;
		std::string getUsername() const;
		
		
		/* SETTERS */
		void setClientAuthentication(bool status);
		void setNickname(std::string nickname);
		void setUsername(std::string username);

};

#endif
