/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:18:21 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/09 21:45:39 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

IRCChannel::~IRCChannel()
{
}

IRCChannel::IRCChannel(std::string name)
{
	_name = name;
}

bool IRCChannel::AddUser(std::string user)
{
	if (std::find(_users.begin(), _users.end(), user) != std::end(_users))
	{
		_users.push_back(user);
		return true;
	}
	return false;
}
bool IRCChannel::DelUser(std::string user)
{
	mapChannelUsers::iterator it;
	
	it = std::find(_users.begin(), _users.end(), user);
	if (it != std::end(_users))
	{
		_users.erase(it);
		return true;
	}
	return false;
}
