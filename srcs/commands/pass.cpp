/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:03:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/08 12:34:24 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#pass-message

#include "../IRCIncludes.hpp"

void pass(IRCClient &client, std::string param, std::string password)
{
	if (client.getClientAuthentication())
		client.SendIRCMsg(ERR_ALREADYREGISTERED(client.user));
	else if (param.empty())
		client.SendIRCMsg(ERR_NEEDMOREPARAMS(client.user, "PASS"));
	else if (param == password)
		client.setClientAuthentication(true);
	else
		client.SendIRCMsg(ERR_PASSWDMISMATCH(client.user));		
}
