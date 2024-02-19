/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:07:00 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/19 21:30:39 by cescanue         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCHANNEl_HPP
# define IRCCHANNEl_HPP

#include "IRCIncludes.hpp"

class IRCChannel
{
private:
	std::string 		_name;
	std::string 		_key;
	std::string 		_topic;
	std::string 		_topicuser;
	std::string 		_topictimestamp;
	vectorChannelUsers 	_users;
	vectorChannelUsers 	_operators;
	mapClients 			&_clients;
	std::string 		_flags;
	unsigned int		_maxUsers;
	IRCChannel();
	
public:
	IRCChannel(std::string name, mapClients &clients);
	~IRCChannel();
	void setKey(std::string key);
	std::string getKey(void);
	void setTopic(std::string topic);
	std::string getTopic(void);
	void setTopicTime(std::string time);
	std::string getTopicTime(void);
	void setTopicUser(std::string user);
	std::string getTopicUser(void);
	bool addUser(std::string user);
	bool delUser(std::string user);
	bool addOper(std::string oper);
	bool delOper(std::string oper);
	vectorChannelUsers getUsers(void);
	vectorChannelUsers getOpers(void);
	std::string getListUsers(void);
	void sendMsg(IRCClient &Client, std::string msg, bool sendtome = true);
	bool checkUser(std::string user);
	bool checkOper(std::string oper);
	bool setFlag(char flag);
	bool removeFlag(char flag);
	bool checkFlag(char flag);
	std::string getFlags(void);
	void changeUserName(std::string oldName, std::string newName);
	void changeOperatorName(std::string oldName, std::string newName);
	void setMaxUsers(unsigned int max);
	unsigned int getMaxUsers(void);
};

#endif

