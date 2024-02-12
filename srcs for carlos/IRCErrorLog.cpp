/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCErrorLog.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:17:14 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/08 10:26:31 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCIncludes.hpp"

IRCErrorLog::IRCErrorLog()
{
	return ;
}

IRCErrorLog::~IRCErrorLog()
{
	return ;
}

bool	IRCErrorLog::Error(std::string error)
{
	std::cout << "ircserv: " << error << std::endl;
	return true;
}

