/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCErrorLog.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:17:14 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/22 12:07:00 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/IRCIncludes.hpp"

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
	std::cerr << "ircserv: " << error << std::endl;
	return true;
}

