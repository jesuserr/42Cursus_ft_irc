/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:07:00 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/12 22:45:07 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCHANNEl_HPP
# define IRCCHANNEl_HPP

#include "IRCIncludes.hpp"

class IRCChannel
{
private:
	std::string _name;
	std::string _key;
	std::string _topic;
	mapChannelUsers _users;
	mapChannelUsers _operators;
	mapClients &_clients;
	IRCChannel();
public:
	IRCChannel(std::string name, mapClients &clients);
	~IRCChannel();
	void setKey(std::string key);
	std::string getKey(void);
	void setTopic(std::string key);
	std::string getTopic(void);
	bool addUser(std::string user);
	bool delUser(std::string user);
	bool addOper(std::string oper);
	bool delOper(std::string oper);
	mapChannelUsers getUsers(void);
	mapChannelUsers getOpers(void);
	std::string getListUsers(void);
	void sendMsg(IRCClient &Client, std::string msg);
};

#endif

