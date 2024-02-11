/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:07:00 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/11 21:06:35 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCHANNEl_HPP
# define IRCCHANNEl_HPP

#include "IRCIncludes.hpp"

class IRCChannel
{
private:
	std::string _name;
	mapChannelUsers _users;
	mapChannelUsers _operators;
	IRCChannel();
public:
	IRCChannel(std::string name);
	~IRCChannel();
	bool AddUser(std::string user);
	bool DelUser(std::string user);
	bool AddOper(std::string oper);
	bool DelOper(std::string oper);
};

#endif

