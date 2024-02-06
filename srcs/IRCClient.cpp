/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 21:40:16 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/06 16:47:10 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCClient.hpp"

IRCClient::IRCClient() 
{
	_pass = false;
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

bool IRCClient::pass(void)
{
	return _pass;
}

void IRCClient::passok(void)
{
	_pass = true;
}

