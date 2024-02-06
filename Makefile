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
SRCS = IRCserv.cpp IRCErrorLog.cpp IRCClient.cpp IRCSocket.cpp IRCCore.cpp
PATH_SRCS = ./srcs/
PATH_OBJS = ./srcs/objs/
PATH_DEPS = ./srcs/objs/

OBJS = $(addprefix $(PATH_OBJS), $(SRCS:.cpp=.o))
DEPS = $(addprefix $(PATH_DEPS), $(SRCS:.cpp=.d))

INCLUDE = -I./
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
CC = g++
GREEN = "\033[0;92m"
RED = "\033[0;91m"
BLUE = "\033[0;94m"
NC = "\033[37m"

all: $(NAME)

$(PATH_OBJS)%.o: $(PATH_SRCS)%.cpp
	@mkdir -p $(PATH_OBJS)
	$(CC) $(CFLAGS) -MMD $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@echo ${GREEN}$(NAME) " Compiled!\n"${NC};
-include $(DEPS)

clean:
	@rm -rf $(PATH_OBJS)
		
fclean:
	@rm -rf $(PATH_OBJS)
	$(RM) $(NAME) 

re: fclean all

.PHONY: all clean fclean re 
