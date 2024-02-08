/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:40:16 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/08 17:10:49 by jesuserr         ###   ########.fr       */
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
