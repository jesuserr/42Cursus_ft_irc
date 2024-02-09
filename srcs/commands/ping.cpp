/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 10:17:35 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/09 10:56:19 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#ping-message
//https://modern.ircdocs.horse/#pong-message

#include "../IRCIncludes.hpp"

void ping(IRCClient &client, std::string token)
{
	std::string userId = USER_ID(client.getNickname(), client.getUsername());
	client.SendIRCMsg(RPL_PONG(userId, token));
	//std::cout << userId + " PONG :" + token << std::endl;	
}
