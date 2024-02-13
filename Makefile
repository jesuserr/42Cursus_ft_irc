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
SRCS = IRCserv.cpp IRCErrorLog.cpp IRCClient.cpp IRCSocket.cpp IRCCore.cpp \
IRCChannel.cpp IRCCoreCommandsUtils.cpp \
commands/pass.cpp commands/nick.cpp commands/user.cpp commands/ping.cpp \
commands/join.cpp commands/privmsg.cpp commands/mode.cpp
PATH_SRCS = ./srcs/
PATH_OBJS = ./srcs/objs/
PATH_DEPS = ./srcs/objs/

OBJS = $(addprefix $(PATH_OBJS), $(SRCS:.cpp=.o))
DEPS = $(addprefix $(PATH_DEPS), $(SRCS:.cpp=.d))

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

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo ${GREEN}$(NAME) "compiled!\n"${NC};
-include $(DEPS)

clean:
	@rm -rf $(PATH_OBJS)
		
fclean:
	@rm -rf $(PATH_OBJS)
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re 
