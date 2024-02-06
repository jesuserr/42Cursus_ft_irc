/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:49:29 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/06 22:29:59 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCCore.hpp"
#include "IRCCommands.hpp"

std::string IRCCore::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

IRCCore::IRCCore(std::string pass, std::map<int, IRCClient> &clients) : _clients(clients)
{
	_pass = pass;
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
	if (cmd.find("PASS") != std::string::npos)
	{
		pass(client, cmd, param, _pass);
		/* if (param == _pass)
		{
			client.passok();
			return;
		} */
	}
	else if (cmd.find("NICK") != std::string::npos)
	{
		client.nick = param;
	}
	else if (cmd.find("USER") != std::string::npos)
	{
		client.user = param;
		if (client.pass() && client.nick.size() && client.user.size())
			client.SendIRCMsg(RPL_WELCOME(client.nick, client.nick));
	}
	
	std::cout << cmd << ":" << param << std::endl;

}
