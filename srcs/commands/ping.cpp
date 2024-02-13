/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:17:35 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/13 21:36:21 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#ping-message
//https://modern.ircdocs.horse/#pong-message

#include "../IRCIncludes.hpp"

void IRCCore::ping(IRCClient &client, std::string token)
{
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	client.SendIRCMsg(RPL_PONG(userId, token));
}
