/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:32:58 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/12 13:05:05 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://modern.ircdocs.horse/#privmsg-message

#include "../IRCIncludes.hpp"

bool privmsgParsing(std::string parameters, std::string *target, std::string *message)
{
	std::stringstream ss(parameters);
	std::getline(ss, *target, ' ');
	std::getline(ss, *message, '\0');
	if (target->empty() || message->empty())
		return (false);
	if ((target->find_first_not_of(VALID_USER_CHARSET) != std::string::npos))
		return (false);
	if ((*message)[0] != ':')
		return (false);
	message->erase(0, 1);
	return (true);
}

void IRCCore::privmsg(IRCClient &client, std::string parameters)
{
	if (!client.getClientRegistration())
	{
		client.SendIRCMsg(ERR_NOTREGISTERED());
		return;
	}
	std::string target;
	std::string message;
	target.clear();
	message.clear();
	if (privmsgParsing(removeTabsAndMultipleSpaces(parameters), &target, &message))
	{
		//define RPL_MESSAGE
		//buscar nick
		//enviar mensaje		
		std::cout << target << std::endl;
		std::cout << message << std::endl;
	}
	else if (target.empty() || parameters.empty())
		client.SendIRCMsg(ERR_NORECIPIENT(client.getUsername()));
	else if (message.empty() || message[0] != ':')
		client.SendIRCMsg(ERR_NOTEXTTOSEND(client.getUsername()));
	else if ((target.find_first_not_of(VALID_USER_CHARSET) != std::string::npos))
		client.SendIRCMsg(ERR_NOSUCHNICK(client.getUsername(), client.getNickname()));
}
