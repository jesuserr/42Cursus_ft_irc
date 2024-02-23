# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cescanue <cescanue@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 20:51:18 by cescanue          #+#    #+#              #
#    Updated: 2024/02/05 20:51:18 by cescanue         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
SRCS = main.cpp IRCErrorLog.cpp IRCClient.cpp IRCSocket.cpp IRCCore.cpp \
IRCChannel.cpp IRCCoreCommandsUtils.cpp \
commands/pass.cpp commands/nick.cpp commands/user.cpp commands/ping.cpp \
commands/join.cpp commands/privmsg.cpp commands/modechannel.cpp commands/part.cpp \
commands/modeuser.cpp commands/quit.cpp commands/topic.cpp commands/kick.cpp \
commands/whois.cpp commands/list.cpp commands/invite.cpp
PATH_SRCS = ./srcs/
PATH_OBJS = ./srcs/objs/
PATH_DEPS = ./srcs/objs/
OBJS = $(addprefix $(PATH_OBJS), $(SRCS:.cpp=.o))
DEPS = $(addprefix $(PATH_DEPS), $(SRCS:.cpp=.d))

BOT_NAME = ircbot
BOT_SRCS = bot.cpp botUtils.cpp
BOT_PATH_SRCS = ./srcs/bot/
BOT_PATH_OBJS = ./srcs/bot/objs/
BOT_PATH_DEPS = ./srcs/bot/objs/
BOT_OBJS = $(addprefix $(BOT_PATH_OBJS), $(BOT_SRCS:.cpp=.o))
BOT_DEPS = $(addprefix $(BOT_PATH_DEPS), $(BOT_SRCS:.cpp=.d))

INCLUDE = -I./
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -g
CC = g++
GREEN = "\033[0;92m"
NC = "\033[37m"

all: $(NAME)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.cpp
	@mkdir -p $(PATH_OBJS)
	@mkdir -p $(PATH_OBJS)/commands
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

$(BOT_PATH_OBJS)%.o: $(BOT_PATH_SRCS)%.cpp
	@mkdir -p $(BOT_PATH_OBJS)	
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo ${GREEN}$(NAME) "compiled!\n"${NC};
-include $(DEPS)

bot: $(BOT_NAME)

$(BOT_NAME): $(BOT_OBJS)
	$(CC) $(CFLAGS) $(BOT_OBJS) -o $@
	@echo ${GREEN}$(BOT_NAME) "compiled!\n"${NC};
-include $(BOT_DEPS)

clean:
	@rm -rf $(PATH_OBJS)
	@rm -rf $(BOT_PATH_OBJS)
		
fclean:
	@rm -rf $(PATH_OBJS)
	@rm -rf $(BOT_PATH_OBJS)
	$(RM) $(NAME) $(BOT_NAME)

re: fclean all

.PHONY: all bot clean fclean re 
