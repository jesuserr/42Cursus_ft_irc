/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:32:58 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/12 10:46:34 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://modern.ircdocs.horse/#privmsg-message

#include "../IRCIncludes.hpp"

void IRCCore::privmsg(IRCClient &client, std::string parameters)
{
	(void)parameters;
	if (!client.getClientRegistration())
	{
		client.SendIRCMsg(ERR_NOTREGISTERED());
		return;
	}
	client.SendIRCMsg(ERR_NORECIPIENT(client.getUsername()));
	client.SendIRCMsg(ERR_NOTEXTTOSEND(client.getUsername()));
	client.SendIRCMsg(ERR_NOSUCHNICK(client.getUsername(), client.getNickname()));
}
