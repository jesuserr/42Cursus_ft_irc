/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:29:16 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/20 11:50:50 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IRCIncludes.hpp"

void IRCCore::list(IRCClient &client, std::string parameters)
{
	parameters = trim(parameters);
	if (parameters.size() == 1)
		parameters.clear();
	if (parameters.empty())
	{
		client.SendIRCMsg(RPL_LISTSTART(client.getNickname()));
		for (mapChannelList::iterator it = _channels.begin(); it != _channels.end(); it++)
		{
			client.SendIRCMsg(RPL_LIST(client.getNickname(), it->second.getName(), std::to_string(it->second.getUsers().size()), it->second.getTopic()));
		}
		client.SendIRCMsg(RPL_LISTEND(client.getNickname()));
	}
	else
	{
		std::cout << "parameters: " << parameters.size() << std::endl;
		if (_channels.find(parameters) == _channels.end())
		{
			client.SendIRCMsg(ERR_NOSUCHCHANNEL(client.getNickname(), parameters));
			return;
		}
		client.SendIRCMsg(RPL_LIST(client.getNickname(), parameters, std::to_string(_channels.find(parameters)->second.getUsers().size()), _channels.find(parameters)->second.getTopic()));
	}
}
