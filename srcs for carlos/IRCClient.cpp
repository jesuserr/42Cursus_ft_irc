/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:40:16 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/08 23:22:21 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

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
