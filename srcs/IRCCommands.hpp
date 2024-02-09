/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommands.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:31:55 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/09 10:55:10 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCOMMANDS_H
# define IRCCOMMANDS_H

# include "IRCIncludes.hpp"

void pass(IRCClient &client, std::string input, std::string password);
void nick(IRCClient &client, std::string newNick, mapClients &_clients);
void user(IRCClient &client, std::string parameters, std::string serverTime);
void ping(IRCClient &client, std::string token);

#endif
