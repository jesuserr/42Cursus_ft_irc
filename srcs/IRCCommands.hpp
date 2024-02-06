/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCCommands.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 21:31:55 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/06 22:29:08 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCOMMANDS_H
# define IRCCOMMANDS_H

# include "IRCCore.hpp"
# include "IRCSocket.hpp"
# include "IRCReplies.hpp"
# include "IRCClient.hpp"

void pass(IRCClient &client, std::string cmd, std::string param, std::string pass);

#endif
