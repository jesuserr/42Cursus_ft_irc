/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCmain.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:25:09 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/01 21:47:36 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IRCErrorLog.hpp"
#include "IRCSocket.hpp"
#include "IRCBasic.hpp"


int main(void)
{

	std::map<int, s_socketdata> m;
	IRCErrorLog log;
	IRCSocket IRC(6667, &log);
	IRC.IRClisten();
	
	while (IRC.IRCPoll(m))
	{
		//system("clear");
		for(std::map<int,s_socketdata>::iterator it = m.begin(); it != m.end(); ++it) 
		{
			std::cout << it->first << ":" << it->second.in << std::endl;
			it->second.out = "Devuelto\n";
		}
	}
	
	
}
