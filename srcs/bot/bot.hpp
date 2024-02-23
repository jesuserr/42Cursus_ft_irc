/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:49:49 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/23 10:57:31 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
# define BOT_HPP

# include <sys/socket.h>
# include <iostream>
# include <arpa/inet.h>
# include <csignal>
# define BUFFER_SIZE	8192

int errorMessage(std::string message);
void welcomeMessageSerious(std::string channel);
void welcomeMessageFunny(std::string channel);
void cleanExit(int signal);

#endif
