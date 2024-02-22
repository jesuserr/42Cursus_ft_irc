/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:40:16 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/22 12:07:19 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/IRCIncludes.hpp"

IRCClient::IRCClient() 
{
	_in.clear();
	_out.clear();
	_clientAuthenticated = false;
	_nickname.clear();
	_username = getenv("USER");
	_clientRegistered = false;
	_realname.clear();
}

IRCClient::~IRCClient()
{
}

/*********************************** GETTERS **********************************/

bool IRCClient::getClientAuthentication() const
{
	return _clientAuthenticated;
}

std::string IRCClient::getNickname() const
{
	return _nickname;
}

std::string IRCClient::getUsername() const
{
	return _username;
}

bool IRCClient::getClientRegistration() const
{
	return _clientRegistered;
}

std::string IRCClient::getRealname() const
{
	return _realname;
}

std::string IRCClient::getFlags(void) const
{
	return _flags;
}

/*********************************** SETTERS **********************************/

void IRCClient::setClientAuthentication(bool status)
{
	_clientAuthenticated = status;
}

void IRCClient::setNickname(std::string nickname)
{
	_nickname = nickname;
}

void IRCClient::setUsername(std::string userName)
{
	_username = userName;
}

void IRCClient::setClientRegistration(bool status)
{
	_clientRegistered = status;
}

void IRCClient::setRealname(std::string realname)
{
	_realname = realname;
}

/*********************************** FUNCTIONS ********************************/

std::string &IRCClient::Getin()
{
	return _in;
}

std::string &IRCClient::Getout()
{
	return _out;
}

void IRCClient::SendIRCMsg(std::string msg)
{
	Getout() += msg;
	Getout() += "\r\n";
}

bool IRCClient::setFlag(char flag)
{
	if (checkFlag(flag))
		return true;
	_flags += std::tolower(flag);
	return true;
}

bool IRCClient::removeFlag(char flag)
{
	flag = std::tolower(flag);
	if (_flags.find(flag) == std::string::npos)
		return false;
	_flags.erase(_flags.find(flag), 1);
	return true;
}

bool IRCClient::checkFlag(char flag)
{
	if (_flags.find(std::tolower(flag)) != std::string::npos)
		return true;
	return false;	
}
