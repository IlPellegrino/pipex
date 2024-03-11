# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nromito <nromito@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/26 19:41:57 by nromito           #+#    #+#              #
#    Updated: 2024/02/28 12:28:05 by nromito          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = pipex.c protected_funcs.c protected_funcs_2.c checks_and_path.c get_next_line.c get_next_line_utils.c
SRCS_MAN = main.c
SRCS_BNS = main_bonus.c
ALL_SRCS = ${SRCS} ${SRCS_MAN} ${SRCS_BNS}

OBJS = ${SRCS:.c=.o} ${SRCS_MAN:.c=.o}
OBJS_BNS = ${SRCS:.c=.o} ${SRCS_BNS:.c=.o}
ALL_BNS_OBJ = ${OBJS} ${OBJS_BNS}

PIPEX_H = pipex.h

GNL_H = get_next_line.h

LIBFT_PATH = libft/
LIBFT = libft/libft.a

NONE = '\033[0m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
YELLOW = '\033[0;33m'
BLUE = '\033[0;34m'

COMPILE = cc -Wall -Wextra -Werror -g

all: ${NAME}

${NAME}: ${OBJS} $(PIPEX_H) $(GNL_H)
		make -C ${LIBFT_PATH}
		$(COMPILE) $(OBJS) $(LIBFT) -o $(NAME)
		@echo $(GREEN)"Mandatory Compiled! Great Job out there mate!"$(NONE)

bonus: ${OBJS_BNS} $(PIPEX_H) $(GNL_H)
		make -C ${LIBFT_PATH}
		$(COMPILE) $(OBJS_BNS) $(LIBFT) -o $(NAME)
		@echo $(YELLOW)"Bonus Compiled!"$(NONE)

%.o: %.c
	$(COMPILE) -c $< -o $@

clean:
		@rm -rf $(ALL_BNS_OBJ)
		@make -C $(LIBFT_PATH)
		@echo $(BLUE)"Successfully cleaned!"$(NONE)

fclean: clean
		@rm -rf $(NAME)
		@make fclean -C $(LIBFT_PATH)
		@echo $(BLUE)"Successfully Fcleaned!"$(NONE)

leaks: all
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) here_doc here "cat" "wc" outfile 2> leak_report
	@rm -rf *.o
	@echo $(GREEN)"LEAK REPORT GENERATED!"$(NONE)

re: fclean all

.PHONY: all clean fclean