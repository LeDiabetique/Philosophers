# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdiot <hdiot@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 19:11:03 by hdiot             #+#    #+#              #
#    Updated: 2023/05/23 19:38:51 by hdiot            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        := philo

CC        := gcc
FLAGS    := -Wall -Wextra -Werror -g3 -lpthread

SRCS        :=  main.c check.c utils.c threadutils.c init.c \

OBJS        := $(SRCS:.c=.o)

.c.o:
	@${CC} ${FLAGS} -c $< -o $@

GREEN		:= \033[92m
YELLOW		:= \033[93m
PURPLE 		:= \033[95m
WHITE		:= \033[0m
RM		    := rm -f

${NAME}:	${OBJS}
	@${CC} ${FLAGS} -o ${NAME} ${OBJS}
	@echo "$(PURPLE)Executable $(GREEN)philo created$(WHITE)"
	
all:		${NAME}

clean:
	@${RM} ${OBJS}
	@echo "$(YELLOW)All .o Files inside philo directory deleted$(WHITE)"

fclean:
	@${RM} ${OBJS}
	@${RM} ${NAME}
	@echo "$(PURPLE)$(NAME) $(YELLOW)and .o files inside philo directory deleted$(WHITE)"

re:	fclean all

.PHONY: all clean fclean re
