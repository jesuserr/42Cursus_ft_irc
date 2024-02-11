/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 20:57:22 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/11 22:02:27 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../IRCIncludes.hpp"

void IRCCore::join(IRCClient &client, std::string parameters)
{
	if (!client.getClientRegistration())
	{
		client.SendIRCMsg(ERR_NOTREGISTERED());
		return;
	}
	std::string channels, keys;
	if (parameters.find(" ") != std::string::npos)
	{
		channels = parameters.substr(0, parameters.find(" "));
		parameters.erase(0, parameters.find(" ") + 1);
		keys = parameters;
	}
	else
		channels = parameters;
	while (channels.find(",") != std::string::npos)	
	{
		std::string c;
		std::string k;
		
		c = channels.substr(0, channels.find(","));
		channels.erase(0, channels.find(",") + 1);
		if (keys.find(",") != std::string::npos)
		{
			k = keys.substr(0, keys.find(","));
			keys.erase(0, keys.find(",") + 1);
		}
		else if (keys.empty())
		{
			k = keys;
			keys.clear();
		}
		joinc(client, c, k);
	}
		joinc(client, channels, keys);
}

void IRCCore::joinc(IRCClient &client, std::string channel, std::string key)
{
	(void) client;
	std::cout << "c:" << channel << " k:" << key << std::endl;

}
