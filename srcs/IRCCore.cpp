/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:49:29 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/08 14:21:41 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

std::string IRCCore::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

IRCCore::IRCCore(std::string pass, std::map<int, IRCClient> &clients) : _clients(clients)
{
	_password = pass;
}

void IRCCore::run(void)
{
	for(std::map<int,IRCClient>::iterator it = _clients.begin(); it != _clients.end(); ++it) 
	{
		while(it->second.Getin().find("\r\n") != std::string::npos)
		{
			if (it->second.Getin().find(" ") != std::string::npos)
				Command(it->second, trim(it->second.Getin().substr(0, it->second.Getin().find(" "))), trim(it->second.Getin().substr(it->second.Getin().find(" "), it->second.Getin().find("\r\n") - it->second.Getin().find(" "))));
			else
				Command(it->second, trim(it->second.Getin().substr(0, it->second.Getin().find("\r\n"))), "");
			it->second.Getin().erase(0, it->second.Getin().find("\r\n") + 2);
		}
	}
}

void IRCCore::Command(IRCClient &client, std::string cmd, std::string param)
{
	if (cmd.find("PASS") != std::string::npos && cmd.size() == 4)
		pass(client, param, _password);
	else if (cmd.find("NICK") != std::string::npos && cmd.size() == 4)
		nick(client, param);
	else if (cmd.find("USER") != std::string::npos)
	{
		client.user = param;
		if (client.getClientAuthentication() && client.getNickName().size() && client.user.size())
			client.SendIRCMsg(RPL_WELCOME(client.getNickName(), client.getNickName()));
	}
	//std::cout << cmd << ":" << param << std::endl;
}

// /connect -nocap localhost 6667 1234
