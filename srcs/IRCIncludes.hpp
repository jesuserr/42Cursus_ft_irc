/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCIncludes.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:21:15 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/10 21:04:31 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_HPP
# define INCLUDES_HPP

# define SERVER_NAME				"IRCServer"
# define SERVER_VERSION				"Alpha-0.1"
# define USER_MODES					""
# define CHANNEL_MODES				"itkol"
# define CHANNEL_MODES_WITH_PARAM	"k"

# define VALID_NICK_CHARSET	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_[]\\{}|-"
# define VALID_USER_CHARSET	"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_[]\\{}|-* "
# define NICK_MAX_LENGTH	9

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

# include "IRCClient.hpp"
typedef std::map<int, IRCClient> mapClients;
# include "IRCSocket.hpp"
# include "IRCReplies.hpp"
# include "IRCErrorLog.hpp"
typedef std::vector<std::string> mapChannelUsers;
# include "IRCChannel.hpp"
typedef std::map<std::string, IRCChannel> mapChannelList; 
# include "IRCCore.hpp"

#endif
