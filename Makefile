all: server client

CC = gcc
CFLAGS =
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
SRCS_CLIENT = client.c
SRCS_SERVER = server.c
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)

$(LIBFT):
	make -C $(LIBFT_DIR)

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

bonus : server client

.PHONY: all bonus libft clean fclean re
