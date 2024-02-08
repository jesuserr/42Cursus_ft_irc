/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCIncludes.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:21:15 by jesuserr          #+#    #+#             */
/*   Updated: 2024/02/08 17:45:54 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_HPP
# define INCLUDES_HPP

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

# include "IRCClient.hpp"
typedef std::map<int, IRCClient> mapClients;
# include "IRCCore.hpp"
# include "IRCSocket.hpp"
# include "IRCReplies.hpp"
# include "IRCErrorLog.hpp"
# include "IRCCommands.hpp"

#endif
