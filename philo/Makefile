CC = gcc
FLAGS = -Wall -Wextra -Werror -pthread

NAME = philo

SRC_DIR = src/

MD_OBJ_DIR = obj/

INC_DIR = includes/

SOURCES = clock.c \
	forks.c \
	init.c \
	main.c \
	parsing.c \
	philo.c \
	philo_life.c \
	return.c \
	run.c \
	utils.c

OBJ = $(SOURCES:.c=.o)

OBJS = $(addprefix $(MD_OBJ_DIR), $(OBJ))

all: $(NAME)


$(MD_OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -c $< -o $@ -I $(INC_DIR) 

$(NAME): $(MD_OBJ_DIR) $(OBJS)
	$(CC) $(FLAGS) -o  $@ $(OBJS)

$(MD_OBJ_DIR):
	mkdir  $(MD_OBJ_DIR)

clean:
	rm -f $(OBJS)
	rm -fd $(MD_OBJ_DIR)

fclean: clean 
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re 
