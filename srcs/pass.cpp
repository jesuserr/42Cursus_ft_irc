/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:03:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/07 09:35:05 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#pass-message

#include "IRCCore.hpp"

void pass(IRCClient &client, std::string cmd, std::string param, std::string pass)
{
	if (param.empty())
		std::cout << ERR_NEEDMOREPARAMS(client.user, "PASS");
	else if (cmd.find("PASS") != std::string::npos)
	{
		if (param != pass)
			std::cout << ERR_PASSWDMISMATCH(client.user);				
		else
			{		
			std::cout << "PASS OK" << std::endl;
			client.passok();
			}
	}
}
