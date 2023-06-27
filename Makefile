# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bfresque <bfresque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/27 14:35:05 by bfresque          #+#    #+#              #
#    Updated: 2023/06/27 14:36:29 by bfresque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosopher

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g3

OBJ_DIR_PHILO = srcs/obj_philo

OBJS = $(SRCS:%.c=$(OBJ_DIR_PHILO)/%.o) \

AR = ar rcs

RM = rm -f

$(OBJ_DIR_PHILO)/%.o
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "\033[5;36m-gcc *.c philo done\n\033[0m"
	@echo "\033[1;32m[Make : 'philosophers' is done]\033[0m"

all : $(NAME)

clean :
	@$(RM) $(OBJS)
	@echo "\033[1;33m[.o] Object files removed\033[0m"

fclean : clean
	@$(RM) $(NAME)
	@echo "\033[1;33m[.a] Binary file removed\033[0m"

re : fclean all

.PHONY: all clean fclean re