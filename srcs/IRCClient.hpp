/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:34:14 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/06 16:58:21 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCLIENT_HPP
# define IRCCLIENT_HPP

# include <string>
# include <iostream>

class IRCClient
{
	private:
		std::string _in;
		std::string _out;
		//test para borrar
		bool _pass;
		

	public:
		IRCClient();
		~IRCClient();
		std::string &Getin();
		std::string &Getout();
		void SendIRCMsg(std::string msg);
		//test para borrar
		bool pass(void);
		void passok(void);
		std::string nick;
		std::string user;
};

#endif
