/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:03:45 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/08 10:34:40 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://modern.ircdocs.horse/#pass-message

#include "../IRCIncludes.hpp"

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
