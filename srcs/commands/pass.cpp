/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:03:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/08 18:32:41 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#pass-message

#include "../IRCIncludes.hpp"

void pass(IRCClient &client, std::string input, std::string password)
{
	if (client.getClientAuthentication())
		client.SendIRCMsg(ERR_ALREADYREGISTERED(client.getUsername()));
	else if (input.empty())
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "PASS"));
	else if (input == password)
		client.setClientAuthentication(true);
	else
		client.SendIRCMsg(ERR_PASSWDMISMATCH(client.getUsername()));		
}
