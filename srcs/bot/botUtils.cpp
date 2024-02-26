/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   botUtils.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:49:01 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/26 17:16:49 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"

int errorMessage(std::string message)
{
	std::system("stty echo");
	std::cerr << " ircbot: " << message << "\033[?25h" << std::endl;	
	return (1);	
}

void welcomeMessageSerious(std::string channel)
{
	std::system("clear");
	std::cout << "\033[?25l";
	std::cout << "    _            _           _   \n"
				"   (_)          | |         | |  \n"
				"    _ _ __ ___  | |__   ___ | |_ \n"
				"   | | '__/ __| | '_ \\ / _ \\| __|		\n"
				"   | | | | (__  | |_) | (_) | |_		\n"
				"   |_|_|  \\___| |_.__/ \\___/ \\__|	\n";
	std::cout << " by Carlos Escañuela & Jesús Serrano\n";
	std::cout << "\n Bot connected to server on channel: " << channel << "\n\n";
}

void welcomeMessageFunny(std::string channel)
{
	std::system("clear");
	std::cout << "\033[?25l";
	std::cout << "     _           _   _  _       \n"
				"    | |__   ___ | |_(_)(_) ___  \n"
				"    | '_ \\ / _ \\| __| || |/ _ \\ \n"
				"    | |_) | (_) | |_| || | (_) | \n"
				"    |_.__/ \\___/ \\__|_|/ |\\___/  \n"
				"                     |__/        \n";
	std::cout << " by Carlos Escañuela & Jesús Serrano\n";
	std::cout << "\n Bot connected to server on channel: " << channel << "\n\n";
}

void cleanExit(int signal)
{
	(void) signal;
	std::system("stty echo");
	std::cout << "\b\b Bot disconnected - See you soon!\n\n\033[?25h";
	exit(0);
}

void sendMessage(int clientSocket, std::string channel, std::string message)
{
	std::string response = "PRIVMSG " + channel + " :" + message + "\r\n";
	send(clientSocket, response.c_str(), response.size(), 0);	
}
