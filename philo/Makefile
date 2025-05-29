NAME = philo

CC = cc
CFLAGS = -fsanitize=address -Wall -Wextra -Werror




SRCS = main.c utils.c garbage_collector.c philo_actions.c helper_function.c
OBJS = $(SRCS:.c=.o)


all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -lpthread $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
