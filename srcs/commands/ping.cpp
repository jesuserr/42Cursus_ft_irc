/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:17:35 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/11 20:19:37 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#ping-message
//https://modern.ircdocs.horse/#pong-message

#include "../IRCIncludes.hpp"

void IRCCore::ping(IRCClient &client, std::string token)
{
	if (!client.getClientRegistration())
	{
		client.SendIRCMsg(ERR_NOTREGISTERED());
		return;
	}
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	client.SendIRCMsg(RPL_PONG(userId, token));
}
