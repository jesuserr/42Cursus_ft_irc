/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modeuser.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:57:20 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/20 11:57:22 by cescanue         ###   ########.fr       */
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
	client.SendIRCMsg(RPL_UMODEIS(client.getNickname(), client.getFlags()));
}

void IRCCore::modeUserMinusI(IRCClient &client)
{
	client.removeFlag('i');
	client.SendIRCMsg(RPL_UMODEIS(client.getNickname(), client.getFlags()));
}




