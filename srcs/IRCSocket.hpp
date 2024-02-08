/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCSocket.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 18:53:22 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/08 17:41:44 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_SOCKET_HPP
# define IRC_SOCKET_HPP

# include "IRCIncludes.hpp"

# define MAXFDS 32000
# define MAXLISTENQUEUE 32000
# define BUFFERSIZE 1024

class IRCErrorLog;

class IRCSocket
{
	private:
		IRCSocket();
		IRCSocket(IRCSocket const &src);
		IRCSocket &operator=(IRCSocket const &rhs);
		IRCErrorLog *_log;
		int _listenPort;
		struct pollfd _fds[MAXFDS];
		int	_nfds;
		bool _listening;
		bool _compressfds;
		void compressFDS(void);
		void deleteSDMAP(mapClients &mapdata, int c);

	public:
		~IRCSocket();
		IRCSocket(int port, IRCErrorLog *log);
		bool IRClisten(void);
		bool IRCPoll(mapClients &mapdata);
		bool IRCSend(mapClients &mapdata);
};

#endif
