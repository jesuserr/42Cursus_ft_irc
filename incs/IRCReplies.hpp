/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCReplies.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 21:33:57 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/22 11:16:07 by jesuserr         ###   ########.fr       */
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
// PRIVMSG messages - channel
# define RPL_PRIVMSGCHANNEL(userid, channelname, msg) (userid + " PRIVMSG " + channelname + " " + msg)
# define ERR_CANNOTSENDTOCHAN(client ,channelname) (":localhost 404 " + client + " " + channelname + " :Cannot send to channel")

// JOIN messages
# define RPL_JOINCHANNEL(userid, channelname) (userid + " JOIN :" + channelname)
# define RPL_NAMREPLY(channelname, nick, users) (":localhost 353 " + nick + " = " + channelname + " :" + users) 
# define RPL_ENDOFNAMES(channelname, nick) (":localhost 366 " + nick + " " + channelname + " :End of NAMES list")
# define ERR_BADCHANNELKEY(client, channelname) (":localhost 475 " + client + " " + channelname + " :Cannot join channel (+k)")
# define ERR_NOSUCHCHANNEL(client, channelname) (":localhost 403 " + client + " " + channelname + " :No such channel")
# define ERR_CHANNELISFULL(client, channel) (":localhost 471 " + client + " " + channel + " :Cannot join channel (+l)")
# define ERR_INVITEONLYCHAN(client, channel) (":localhost 473 " + client + " " + channel + " :Cannot join channel (+i)")

// TOPIC messages
# define RPL_NOTOPIC(client, channelname) (":localhost 331 " + client + " " + channelname + " :No topic is set")
# define RPL_TOPIC(nick, channelname, topic) (":localhost 332 " + nick + " " + channelname + " :" + topic)
# define RPL_TOPICSET(userid, channelname, topic) (userid  + " TOPIC " + channelname + " :" + topic)
# define RPL_TOPICWHOTIME(nick, channelname, topicuser, timestamp) (":localhost 333 " + nick + " " + channelname + " " + topicuser + " " + timestamp)  

// MODE channelmessages
# define ERR_CHANOPRIVSNEEDED(client, channelname) (":localhost 482 " + client + " " + channelname + " :You're not channel operator")
# define ERR_BADCHANMASK(channelname) (":localhost 476 " + channelname + " :Bad Channel Mask")
# define ERR_UNKNOWNMODE(client, mode, channelname) (":localhost 472 " + client + " " + mode + " :is unknown mode char to me for " + channelname)
# define RPL_CHANNELMODEIS(userid, channelname, mode, parameters) (userid + " MODE " + channelname + " " + mode + " " + parameters)
# define RPL_CHANNELMODEISBYSERVER(client, channelname, mode, parameters) (":localhost 324 MODE " + client + " " + channelname + " +" + mode + " " + parameters)

// MODE usermessages
# define ERR_UMODEUNKNOWNFLAG(client) (":localhost 501 " + client + " :Unknown MODE flag")
# define ERR_USERSDONTMATCH(client) (":localhost 502 " + client + " :Cannot change mode for other users")
# define RPL_UMODEIS(client, mode) (":localhost 221 " + client + " " + mode)

// PART messages
# define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " " + channel + " :You're not on that channel")
# define RPL_PARTCHANNEL(USER_ID, channelname, message) (USER_ID + " PART " + channelname + " " + message)

// QUIT messages
# define RPL_QUITCHANNEL(USER_ID, message) (USER_ID + " QUIT " + message)

// KICK messages
# define ERR_USERNOTINCHANNEL(client, nick, channel) (":localhost 441 " + client + " " + nick + " " + channel + " :They aren't on that channel")
# define RPL_KICKCHANNEL(USER_ID, channel, user, message) (USER_ID + " KICK " + channel + " " + user + " " + message)

// WHOIS messages
# define RPL_WHOISUSER(client, nick, user, host, server, realname) (":localhost 311 " + client + " " + nick + " " + user + " " + host + " * :" + realname)
# define RPL_WHOISSERVER(client, nick, server, serverinfo) (":localhost 312 " + client + " " + nick + " " + server + " :" + serverinfo)
# define RPL_WHOISOPERATOR(client, nick) (":localhost 313 " + client + " " + nick + " :is an IRC operator")
# define RPL_WHOISIDLE(client, nick, idle, signon) (":localhost 317 " + client + " " + nick + " " + idle + " " + signon + " :seconds idle, signon time")
# define RPL_ENDOFWHOIS(client, nick) (":localhost 318 " + client + " " + nick + " :End of WHOIS list")

// LIST messages
# define RPL_LISTSTART(client) (":localhost 321 " + client + " :Channel :Users Name")
# define RPL_LIST(client, channel, users, topic) (":localhost 322 " + client + " " + channel + " " + users + " :" + topic)
# define RPL_LISTEND(client) (":localhost 323 " + client + " :End of LIST")

// INVITE messages
# define ERR_USERONCHANNEL(client, nick, channel) (":localhost 443 " + client + " " + nick + " " + channel + " :is already on channel")
# define RPL_INVITING(client, nick, channel) (":localhost 341 " + client + " " + nick + " " + channel)
# define RPL_INVITE(USER_ID, nick, channel) (USER_ID + " INVITE " + nick + " " + channel)

#endif
