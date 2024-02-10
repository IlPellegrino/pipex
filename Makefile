# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nromito <nromito@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 11:44:56 by nromito           #+#    #+#              #
#    Updated: 2024/02/10 11:54:49 by nromito          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = pipex.c

OBJS = ${SRCS:.c=.o}

LIB_H = lib.h

LIBFT_PATH = libft/
LIBFT = libft/libft.a

NONE = '\033[0m'
GREEN = '\033[32m'

COMPILE = cc -Wall -Wextra -Werror -g

all: ${NAME}

${NAME}: ${OBJS}
		make -C ${LIBFT_PATH}
		$(COMPILE) $(OBJS) $(LIBFT) -o $(NAME)
		@echo $(GREEN) "Successfully Compiled! Great Job out there mate!" $(NONE)

$(OBJS): $(SRCS) $(LIB_H)
		$(COMPILE) -c $(SRCS)

clean:
		@rm -rf $(OBJS)
		@make -C $(LIBFT_PATH)

fclean: clean
		@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean