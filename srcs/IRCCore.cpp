/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCore.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:26:24 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/09 11:50:17 by jesuserr         ###   ########.fr       */
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

std::string IRCCore::obtainStartingTime(void)
{
	time_t		elapsed_time;
	struct tm	*time_info;
	char		time_stamp[20];

	elapsed_time = time(NULL);
	time_info = localtime(&elapsed_time);
	strftime(time_stamp, 20, "%Y-%m-%d %H:%M:%S", time_info);
	return (time_stamp);
}	

void IRCCore::run(void)
{
	for(mapClients::iterator it = _clients.begin(); it != _clients.end(); ++it) 
	{
		while(it->second.Getin().find("\r\n") != std::string::npos)
		{
			if (it->second.Getin().find(" ") != std::string::npos)
				Command(_clients, it->second, trim(it->second.Getin().substr(0, it->second.Getin().find(" "))), trim(it->second.Getin().substr(it->second.Getin().find(" "), it->second.Getin().find("\r\n") - it->second.Getin().find(" "))));
			else
				Command(_clients, it->second, trim(it->second.Getin().substr(0, it->second.Getin().find("\r\n"))), "");
			it->second.Getin().erase(0, it->second.Getin().find("\r\n") + 2);
		}
	}
}

void IRCCore::Command(mapClients &_clients, IRCClient &client, std::string cmd, std::string param)
{
	if (cmd.find("PASS") != std::string::npos && cmd.size() == 4)
		pass(client, param, _password);
	else if (cmd.find("NICK") != std::string::npos && cmd.size() == 4)
		nick(client, param, _clients);
 	else if (cmd.find("USER") != std::string::npos && cmd.size() == 4)
		user(client, param, _startingTime);
	else if (cmd.find("LEAKSCHECKEXIT") != std::string::npos && cmd.size() == 14)
		throw std::runtime_error("\b\b   Server disconnected - See you soon!\n");		
	else if (cmd.find("PING") != std::string::npos && cmd.size() == 4)
		ping(client, param);
}

// /connect -nocap localhost 6667 1234
