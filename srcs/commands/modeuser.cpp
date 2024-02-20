/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeuser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:34:03 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/20 11:29:27 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IRCIncludes.hpp"

void IRCCore::modeUser(IRCClient &client, std::string user, std::string flags)
{
	if (user != client.getNickname())
	{
		client.SendIRCMsg(ERR_USERSDONTMATCH(client.getNickname()));
		return;
	}
	if (flags.at(0) == '+')
	{
		flags.erase(0, 1);
		while (!flags.empty())
		{
			if (std::tolower(flags.at(0)) == 'i')
				modeUserPlusI(client);
			else 
				client.SendIRCMsg(ERR_UMODEUNKNOWNFLAG(client.getNickname()));
			flags.erase(0, 1);
		}
	}
	else 
	{
		flags.erase(0, 1);
		while (!flags.empty())
		{
			if (std::tolower(flags.at(0)) == 'i')
				modeUserMinusI(client);
			else 
				client.SendIRCMsg(ERR_UMODEUNKNOWNFLAG(client.getNickname()));
			flags.erase(0, 1);
		}
	}
}

void IRCCore::modeUserPlusI(IRCClient &client)
{
	client.setFlag('i');
}

void IRCCore::modeUserMinusI(IRCClient &client)
{
	client.removeFlag('i');
}




