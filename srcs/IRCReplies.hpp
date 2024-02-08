/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCReplies.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:24:33 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/08 11:33:38 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCREPLIES_HPP
# define IRCREPLIES_HPP

// by default irssi sets client with $USER
# define user_id(nickname, client) (":" + nickname + "!" + client + "@localhost")

// PASS & USER messages
# define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters")
# define ERR_ALREADYREGISTERED(client) (":localhost 462 " + client + " :You may not reregister")
# define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect")

// NICK messages
# define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " :No nickname given")
# define ERR_ERRONEUSNICKNAME(client, nick) (":localhost 432 " + client + " " + nick + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nick) (":localhost 433 " + client + " " + nick + " :Nickname is already in use")
# define RPL_NICK(user_id, newNick) (user_id + " NICK " +  newNick + "")    //send RPL before updating the nickname

// WELCOME messages
# define RPL_WELCOME(client, user_id) (":localhost 001 " + client + " :Welcome to the Internet Relay Network " + user_id + "")
# define RPL_YOURHOST(client, servername, version) (":localhost 002 " + client + " :Your host is " + servername + ", running version " + version + "")
# define RPL_CREATED(client, datetime) (":localhost 003 " + client + " :This server was created " + datetime + "")
# define RPL_MYINFO(client, servername, version, availableUserModes, availableChannelModes, channelModesWithParam) \
    (":localhost 004 " + client + " " + servername + " " + version + " " + availableUserModes + " " + availableChannelModes + " " + channelModesWithParam"")
# define RPL_ISUPPORT(client, supportedTokens) (":localhost 005 " + client + " " + supportedTokens + " :are supported by this server")

#endif
