/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:26:24 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/12 23:07:35 by cescanue         ###   ########.fr       */
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

IRCCore::IRCCore(std::string pass, mapClients &clients) : _clients(clients)
{
	_password = pass;
	_startingTime = obtainStartingTime();
}

void IRCCore::run(void)
{
	for(mapClients::iterator it = _clients.begin(); it != _clients.end(); ++it) 
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

void IRCCore::uppercaseCommand(std::string &cmd)
{
	if (!cmd.empty())
		for (std::string::iterator it = cmd.begin(); it != cmd.end(); ++it)
		    *it = std::toupper(*it);	
}

void IRCCore::Command(IRCClient &client, std::string cmd, std::string param)
{
	uppercaseCommand(cmd);	
	if (cmd.find("PASS") != std::string::npos && cmd.size() == 4)
		pass(client, param, _password);
	else if (cmd.find("NICK") != std::string::npos && cmd.size() == 4)
		nick(client, param);
 	else if (cmd.find("USER") != std::string::npos && cmd.size() == 4)
		user(client, param);
	else if (cmd.find("LEAKSCHECKEXIT") != std::string::npos && cmd.size() == 14)
		throw std::runtime_error("\b\b   Server disconnected - See you soon!\n");		
	else if (cmd.find("PING") != std::string::npos && cmd.size() == 4)
		ping(client, param);
	else if (cmd.find("JOIN") != std::string::npos && cmd.size() == 4)
		join(client, param);
	else if (cmd.find("PRIVMSG") != std::string::npos && cmd.size() == 7)
		privmsg(client, param);
	else if (!client.getClientRegistration())
		client.SendIRCMsg(ERR_NOTREGISTERED());
	else if (client.getClientRegistration())
		client.SendIRCMsg(ERR_UNKNOWNCOMMAND(client.getUsername(), cmd));		

	//std::cout << "cmd:" << cmd << " param:" << param << std::endl;
}

// /connect -nocap localhost 6667 1234