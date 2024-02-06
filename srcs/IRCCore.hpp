/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:43:30 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/06 17:17:08 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCORE_HPP
# define IRCCORE_HPP

# include <iostream>
# include <string>
# include <map>
# include "IRCClient.hpp"
# include "IRCReplies.hpp"

class IRCCore
{
	private:
		IRCCore();
		IRCCore(IRCCore const &cpy);
		IRCCore &operator=(IRCCore const &rhs);
		std::map<int, IRCClient> &_clients;
		std::string _pass;
		std::string trim(const std::string& str);
	
	public:	
		IRCCore(std::string pass, std::map<int, IRCClient> &clients);
		void run(void);
		void Command(IRCClient &client, std::string cmd, std::string param);
};

#endif