NAME = philo

CC = cc
CFLAGS = -g3  -Wall -Wextra -Werror -pthread




SRCS = main.c utils.c garbage_collector.c philo_actions.c helper_function.c init_vars.c
OBJS = $(SRCS:.c=.o)

TSAN = -fsanitize=thread
ASAN = -fsanitize=address
all: $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tsan: 
	$(CC) $(CFLAGS)  $(SRCS) $(TSAN) -o $(NAME)
asan:
	$(CC) $(CFLAGS)  $(SRCS) $(ASAN) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
