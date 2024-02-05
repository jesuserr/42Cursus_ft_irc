/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCErrorLog.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:15:02 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/31 21:08:28 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_ERROR_LOG_HPP
# define IRC_ERROR_LOG_HPP

#include <string>
#include <iostream>

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

