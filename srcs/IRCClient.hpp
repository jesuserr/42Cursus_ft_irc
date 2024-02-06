/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:34:14 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/06 13:48:03 by cescanue         ###   ########.fr       */
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

	public:
		IRCClient();
		~IRCClient();
		std::string &Getin();
		std::string &Getout();

};

#endif
