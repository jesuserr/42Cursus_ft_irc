/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCChannel.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesuserr <jesuserr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 21:07:00 by cescanue          #+#    #+#             */
/*   Updated: 2024/02/21 09:24:06 by jesuserr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCCHANNEl_HPP
# define IRCCHANNEl_HPP

# include "IRCIncludes.hpp"

class IRCChannel
{
	private:
		IRCChannel();
		
		std::string 		_name;
		std::string 		_key;
		std::string 		_topic;
		std::string 		_topicuser;
		std::string 		_topictimestamp;
		vectorChannelUsers 	_users;
		vectorChannelUsers 	_operators;
		vectorChannelUsers 	_invited;
		mapClients 			&_clients;
		std::string 		_flags;
		unsigned int		_maxUsers;		
		
	public:
		IRCChannel(std::string name, mapClients &clients);
		~IRCChannel();
		
		/***************************** GETTERS ********************************/
		std::string getName(void);
		std::string getKey(void);
		std::string getTopic(void);
		std::string getTopicTime(void);
		std::string getTopicUser(void);
		vectorChannelUsers getUsers(void);
		vectorChannelUsers getOpers(void);
		std::string getListUsers(void);
		unsigned int getMaxUsers(void);
		std::string getFlags(void);
		
		/***************************** SETTERS ********************************/
		void setKey(std::string key);
		void setTopic(std::string topic);
		void setTopicTime(std::string time);
		void setTopicUser(std::string user);
		void setMaxUsers(unsigned int max);
		
		/***************************** FUNCTIONS ******************************/
		bool addUser(std::string user);
		bool delUser(std::string user);
		bool addOper(std::string oper);
		bool delOper(std::string oper);
		void sendMsg(IRCClient &Client, std::string msg, bool sendtome = true);
		bool checkUser(std::string user);
		bool checkOper(std::string oper);
		bool setFlag(char flag);
		bool removeFlag(char flag);
		bool checkFlag(char flag);
		void changeUserName(std::string oldName, std::string newName);
		void changeOperatorName(std::string oldName, std::string newName);
		bool addInvited(std::string user);
		bool delInvited(std::string user);
		bool checkInvited(std::string user);
};

#endif
