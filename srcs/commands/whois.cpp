/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whois.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:20:36 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/IRCIncludes.hpp"

void IRCCore::whois(IRCClient &client, std::string parameters)
{
	std::string nickname;
	
	if (parameters.empty())
	{
		client.SendIRCMsg(ERR_NONICKNAMEGIVEN(client.getNickname()));
		return;
	}
	if (parameters.find(" ") != std::string::npos)
	{
		nickname = parameters.substr(0, parameters.find(" "));
		parameters = parameters.substr(parameters.find(" "), parameters.size());
		parameters = trim(parameters);
	}
	else
	{
		nickname = trim(parameters);
		parameters.clear();
	}
	if (this->checkUser(nickname))
	{
		client.SendIRCMsg(ERR_NOSUCHNICK(client.getNickname(), nickname));
		return;
	}
	client.SendIRCMsg(RPL_WHOISUSER(client.getNickname(), nickname, "", "", "", ""));
	client.SendIRCMsg(RPL_WHOISSERVER(client.getNickname(), nickname, "", ""));
	client.SendIRCMsg(RPL_WHOISOPERATOR(client.getNickname(), nickname));
	client.SendIRCMsg(RPL_ENDOFWHOIS(client.getNickname(), nickname));
}
