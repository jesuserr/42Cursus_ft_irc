/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:49:49 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/24 16:24:28 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <sys/socket.h>
# include <iostream>
# include <arpa/inet.h>
# include <csignal>
# include <netdb.h>
# include <sstream>

# define BUFFER_SIZE	    8192
# define SPANISH_CHARSET    "áéíóúñÁÉÍÓÚÑüÜ"

int errorMessage(std::string message);
void welcomeMessageSerious(std::string channel);
void welcomeMessageFunny(std::string channel);
void cleanExit(int signal);
void sendMessage(int clientSocket, std::string channel, std::string message);

#endif
