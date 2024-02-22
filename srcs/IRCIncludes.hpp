/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCIncludes.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:21:15 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/22 11:37:48 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# define SERVER_NAME				"IRCServer"
# define SERVER_VERSION				"Release Candidate(RC)-1.0"
# define USER_MODES					""
# define CHANNEL_MODES				"itkol"
# define CHANNEL_MODES_WITH_PARAM	"kol"

# define VALID_NICK_CHARSET	    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_[]\\{}|-"
# define VALID_USER_CHARSET	    "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_[]\\{}|-*. "
# define VALID_CHANNEL_CHARSET	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_[]\\{}|-* #@"
# define NICK_MAX_LENGTH	    9
# define MAX_USERS_PER_CHANNEL	100

# include <string>
# include <map>
# include <iostream>
# include <cstdlib>
# include <sys/poll.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <sstream>
# include <ctime>
# include <csignal>
# include <algorithm>
# include <vector>

class IRCChannel;
class IRCClient;
typedef std::vector<std::string> vectorChannelUsers;
typedef std::map<int, IRCClient> mapClients;
typedef std::map<std::string, IRCChannel> mapChannelList; 
# include "IRCClient.hpp"
# include "IRCSocket.hpp"
# include "IRCReplies.hpp"
# include "IRCErrorLog.hpp"
# include "IRCChannel.hpp"
# include "IRCCore.hpp"

#endif
