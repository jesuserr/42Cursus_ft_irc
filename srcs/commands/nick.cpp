/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:14:47 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/08 17:41:44 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#nick-message

#include "../IRCIncludes.hpp"

void nick(IRCClient &client, std::string param, mapClients &_clients)
{
	(void)_clients;
	if (!client.getClientAuthentication())
		return;
	if (param.empty())
		client.SendIRCMsg(ERR_NONICKNAMEGIVEN(client.getUsername()));
	else if ((param.find_first_not_of(VALID_NICK_CHARSET) != std::string::npos) \
	|| (param.size() > NICK_MAX_LENGTH))
		client.SendIRCMsg(ERR_ERRONEUSNICKNAME(client.getUsername(), param));
	else if (param != client.getNickname())
	{
		std::string userId = USER_ID(client.getNickname(), client.getUsername());
		client.SendIRCMsg(RPL_NICK(userId, param));
		client.setNickname(param);		
	}
}
