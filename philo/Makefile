NAME = philo

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror




SRCS = main.c utils.c
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
