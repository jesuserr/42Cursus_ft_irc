/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:29:16 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/22 12:08:57 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/IRCIncludes.hpp"

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
			std::stringstream ss;
    		ss << it->second.getUsers().size();
    		std::string channelsize = ss.str();
			client.SendIRCMsg(RPL_LIST(client.getNickname(), it->second.getName(), channelsize, it->second.getTopic()));
		}
		client.SendIRCMsg(RPL_LISTEND(client.getNickname()));
	}
	else
	{
		if (_channels.find(parameters) == _channels.end())
		{
			client.SendIRCMsg(ERR_NOSUCHCHANNEL(client.getNickname(), parameters));
			return;
		}
		std::stringstream ss;
    	ss << _channels.find(parameters)->second.getUsers().size();
    	std::string channelsize = ss.str();
		client.SendIRCMsg(RPL_LIST(client.getNickname(), parameters, channelsize, _channels.find(parameters)->second.getTopic()));
	}
}

