/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCErrorLog.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:15:02 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/22 12:05:56 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_ERROR_LOG_HPP
# define IRC_ERROR_LOG_HPP

# include "IRCIncludes.hpp"

class IRCErrorLog
{
	private:
		IRCErrorLog(IRCErrorLog const &src);
		IRCErrorLog &operator=(IRCErrorLog const &rhs);

	public:
		~IRCErrorLog();
		IRCErrorLog();
		bool Error(std::string error);
};

#endif

