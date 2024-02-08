/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:34:14 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/08 11:41:56 by jesuserr         ###   ########.fr       */
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

	public:
		IRCClient();
		~IRCClient();
		std::string &Getin();
		std::string &Getout();
		void SendIRCMsg(std::string msg);
		bool getClientAuthentication() const;
		void setClientAuthentication(bool status);
		//test para borrar
		std::string nick;
		std::string user;
};

#endif
