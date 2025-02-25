NAME = minitalk

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS_CLIENT = client.c
SRCS_SERVER = server.c
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

$(NAME): server client

$(LIBFT):
	make -C $(LIBFT_DIR)

all: $(NAME)

client: $(OBJS_CLIENT) $(LIBFT)
	$(CC) $(CFLAGS) -o client $(OBJS_CLIENT) $(LIBFT)

server: $(OBJS_SERVER) $(LIBFT)
	$(CC) $(CFLAGS) -o server $(OBJS_SERVER) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f client server

re: fclean all

.PHONY: all libft clean fclean re
