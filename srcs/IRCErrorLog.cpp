/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCErrorLog.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:17:14 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/05 21:23:09 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCErrorLog.hpp"

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
	std::cout << "ircserv:" << error << std::endl;
	return false;
}

