/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:40:16 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/08 14:19:04 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

IRCClient::IRCClient() 
{
	_in.clear();
	_out.clear();
	_clientAuthenticated = false;
	_nickName.clear();
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

bool IRCClient::getClientAuthentication() const
{
	return _clientAuthenticated;
}

std::string IRCClient::getNickName() const
{
	return _nickName;
}

void IRCClient::setClientAuthentication(bool status)
{
	_clientAuthenticated = status;
}

void IRCClient::setNickName(std::string nick)
{
	_nickName = nick;
}
