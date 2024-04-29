NAME = philo

SRC = checker.c control.c init.c philo.c program.c utils.c

FLAGS = -Wall -Wextra -Werror -o3 -pthread

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS)

fclean:
	@rm -rf $(NAME)
	@rm -rf $(OBJS)

re: fclean all
