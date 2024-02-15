/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCReplies.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 12:11:21 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/15 18:23:05 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCREPLIES_HPP
# define IRCREPLIES_HPP

// by default irssi sets client with $USER
# define USER_ID(nickname, client) (":" + nickname + "!" + client + "@localhost")

// PASS & USER messages
# define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters")
# define ERR_ALREADYREGISTERED(client) (":localhost 462 " + client + " :You may not reregister")
# define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect")

// NICK messages
# define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " :No nickname given")
# define ERR_ERRONEUSNICKNAME(client, nick) (":localhost 432 " + client + " " + nick + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nick) (":localhost 433 " + client + " " + nick + " :Nickname is already in use")
# define RPL_NICK(USER_ID, newNick) (USER_ID + " NICK " +  newNick)    //send RPL before updating the nickname

// WELCOME messages (RPL_WELCOME is wrong in the official documentation, says client instead of nickname)
# define RPL_WELCOME(nickname, USER_ID) (":localhost 001 " + nickname + " :Welcome to the Internet Relay Network " + USER_ID)
# define RPL_YOURHOST(client, servername, version) (":localhost 002 " + client + " :Your host is " + servername + ", running version " + version)
# define RPL_CREATED(client, datetime) (":localhost 003 " + client + " :This server was created " + datetime)
# define RPL_MYINFO(client, servername, version, availableUserModes, availableChannelModes, channelModesWithParam) \
    (":localhost 004 " + client + " " + servername + " " + version + " " + availableUserModes + " " + availableChannelModes + " " + channelModesWithParam"")
# define RPL_ISUPPORT(client, supportedTokens) (":localhost 005 " + client + " " + supportedTokens + " :are supported by this server")

// PING messages
# define RPL_PONG(USER_ID, token) (USER_ID + " PONG :" + token)

// MOTD messages
# define RPL_MOTDSTART(client, servername) (":localhost 375 " + client + " :- " + servername + " Message of the day - ")
# define RPL_MOTD(client, line) (":localhost 372 " + client + " :" + line)
# define RPL_ENDOFMOTD(client) (":localhost 376 " + client + " :End of /MOTD command.")

// GENERIC ERROR messages
# define ERR_NOTREGISTERED() (":localhost 451 :You have not registered")
# define ERR_UNKNOWNCOMMAND(client, command) (":localhost 421 " + client + " " + command + " :Unknown command")

// PRIVMSG messages
# define ERR_NOSUCHNICK(client, nick) (":localhost 401 " + client + " " + nick + " :No such nick/channel")
# define ERR_NORECIPIENT(client) (":localhost 411 " + client + " :No recipient given (PRIVMSG)")
# define ERR_NOTEXTTOSEND(client) (":localhost 412 " + client + " :No text to send")
# define RPL_PRIVMSG(USER_ID, nick, message) (USER_ID + " PRIVMSG " + nick + " " + message)
//PRIVMSG messages - channel
# define RPL_PRIVMSGCHANNEL(userid, channelname, msg) (userid + " PRIVMSG " + channelname + " " + msg)
# define ERR_CANNOTSENDTOCHAN(channelname) (":localhost 404 " + channelname + " :Cannot send to channel")

// JOIN messages
# define RPL_JOINCHANNEL(userid, channelname) (userid + " JOIN :" + channelname)
# define RPL_NAMREPLY(channelname, nick, users) (":localhost 353 " + nick + " = " + channelname + " :" + users) 
# define RPL_ENDOFNAMES(channelname, nick) (":localhost 366 " + nick + " " + channelname + " :End of NAMES list")
# define ERR_BADCHANNELKEY(channelname) (":localhost 475 " + channelname + " :Cannot join channel (+k)")
# define ERR_NOSUCHCHANNEL(channelname) (":localhost 403 " + channelname + " :No such channel")

// TOPIC messages
# define RPL_NOTOPIC(channelname) (":localhost 331 " + channelname + " :No topic is set")
# define RPL_TOPIC(channelname, topic) (":localhost 332 " + channelname + " :" + topic)

// MODE messages
# define ERR_CHANOPRIVSNEEDED(channelname) (":localhost 482 " + channelname + " :You're not channel operator")
# define ERR_BADCHANMASK(channelname) (":localhost 476 " + channelname + " :Bad Channel Mask")
# define ERR_UNKNOWNMODE(mode, channelname) (":localhost 472 " + mode + " :is unknown mode char to me for " + channelname)
# define RPL_CHANNELMODEIS(userid, channelname, mode, parameters) (userid + " MODE " + channelname + " " + mode + " " + parameters)
# define RPL_CHANNELMODEISBYSERVER(channelname, mode, parameters) (":localhost 324 MODE " + channelname + " +" + mode + " " + parameters)

// PART messages
# define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " " + channel + " :You're not on that channel")
# define RPL_PARTCHANNEL(USER_ID, channelname, message) (USER_ID + " PART " + channelname + " " + message)

// QUIT messages
# define RPL_QUITCHANNEL(USER_ID, message) (USER_ID + " QUIT " + message)

#endif
