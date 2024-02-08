/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:14:47 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/08 14:24:24 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#nick-message

#include "../IRCIncludes.hpp"

void nick(IRCClient &client, std::string param)
{
	// client must be authenticated
	
	if (param.empty())
		client.SendIRCMsg(ERR_NONICKNAMEGIVEN(client.user));
	else if ((param.find_first_not_of(VALID_NICK_CHARSET) != std::string::npos) \
	|| (param.size() > NICK_MAX_LENGTH))
		client.SendIRCMsg(ERR_ERRONEUSNICKNAME(client.user, param));	
	else
		client.setNickName(param);
	std::cout << "NICK: " << client.getNickName() << std::endl;
}
