/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCBasic.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:26:19 by cescanue          #+#    #+#             */
/*   Updated: 2024/01/31 21:29:05 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCBASIC_HPP
# define IRCBASIC_HPP

#include <string>

typedef struct s_socketdata
{
	std::string in;
	std::string out;
}	t_socketdata;

#endif