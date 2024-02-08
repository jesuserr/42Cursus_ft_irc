/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:03:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/08 17:09:46 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#pass-message

#include "../IRCIncludes.hpp"

void pass(IRCClient &client, std::string param, std::string password)
{
	if (client.getClientAuthentication())
		client.SendIRCMsg(ERR_ALREADYREGISTERED(client.getUsername()));
	else if (param.empty())
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.getUsername(), "PASS"));
	else if (param == password)
		client.setClientAuthentication(true);
	else
		client.SendIRCMsg(ERR_PASSWDMISMATCH(client.getUsername()));		
}
