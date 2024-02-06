/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:43:30 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/06 20:06:25 by jesuserr         ###   ########.fr       */
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
