/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:35:12 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/26 17:59:39 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/IRCIncludes.hpp"

IRCCore::IRCCore(std::string pass, mapClients &clients, vectorChannelUsers &usersdisconnected) \
: _clients(clients), _usersdisconnected(usersdisconnected)
{
	_password = pass;
	_startingTime = obtainStartingTime();
}

void IRCCore::quitDisconnectedUsers(void)
{
	IRCClient t;
	while (_usersdisconnected.size() && _usersdisconnected[0].find(":") != std::string::npos)
	{
		t.setNickname(_usersdisconnected[0].substr(0, _usersdisconnected[0].find(":")));
		t.setUsername(_usersdisconnected[0].substr(_usersdisconnected[0].find(":") + 1, _usersdisconnected.size()));
		_usersdisconnected.erase(_usersdisconnected.begin());
		quit(t, ":User lost connection");
	}
}

bool IRCCore::checkUser(std::string nickname)
{
	for(mapClients::iterator it = _clients.begin(); it != _clients.end(); ++it) 
	{
		if (it->second.getNickname() == nickname)
			return true;
	}
	return false;
}

void IRCCore::run(void)
{
	quitDisconnectedUsers();
	for(mapClients::iterator it = _clients.begin(); it != _clients.end(); ++it) 
	{
		while(it->second.Getin().find("\r\n") != std::string::npos)
		{
			if (it->second.Getin().find(" ") != std::string::npos)
				command(it->second, trim(it->second.Getin().substr(0, it->second.Getin().find(" "))), \
				trim(it->second.Getin().substr(it->second.Getin().find(" "), it->second.Getin().find("\r\n") \
				- it->second.Getin().find(" "))));
			else
				command(it->second, trim(it->second.Getin().substr(0, it->second.Getin().find("\r\n"))), "");
			it->second.Getin().erase(0, it->second.Getin().find("\r\n") + 2);
		}
	}
}

void IRCCore::command(IRCClient &client, std::string cmd, std::string param)
{
	uppercaseCommand(cmd);	
	if (cmd.find("PASS") != std::string::npos && cmd.size() == 4)
		pass(client, param, _password);
	else if (cmd.find("NICK") != std::string::npos && cmd.size() == 4)
		nick(client, param);
 	else if (cmd.find("USER") != std::string::npos && cmd.size() == 4)
		user(client, param);
	else if (cmd.find("CAP") != std::string::npos && cmd.size() == 3)
		;
	else if (!client.getClientRegistration())
		client.SendIRCMsg(ERR_NOTREGISTERED());
	else if (cmd.find("PING") != std::string::npos && cmd.size() == 4)
		ping(client, param);
	else if (cmd.find("JOIN") != std::string::npos && cmd.size() == 4)
		join(client, param);
	else if (cmd.find("PRIVMSG") != std::string::npos && cmd.size() == 7)
		privmsg(client, param);
	else if (cmd.find("MODE") != std::string::npos && cmd.size() == 4)
		mode(client, param);
	else if (cmd.find("PART") != std::string::npos && cmd.size() == 4)
		part(client, param);
	else if (cmd.find("QUIT") != std::string::npos && cmd.size() == 4)
		quit(client, param);
	else if (cmd.find("TOPIC") != std::string::npos && cmd.size() == 5)
		topic(client, param);
	else if (cmd.find("KICK") != std::string::npos && cmd.size() == 4)
		kick(client, param);
	else if (cmd.find("WHOIS") != std::string::npos && cmd.size() == 5)
		whois(client, param);
	else if (cmd.find("LIST") != std::string::npos && cmd.size() == 4)
		list(client, param);
	else if (cmd.find("INVITE") != std::string::npos && cmd.size() == 6)
		invite(client, param);
	else if (client.getClientRegistration())
		client.SendIRCMsg(ERR_UNKNOWNCOMMAND(client.getUsername(), cmd));		
}
