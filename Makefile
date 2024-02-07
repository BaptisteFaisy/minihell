NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
# -Imlx_linux -I/usr/include
# -I/usr/include -Imlx-linux/lib -lmlx-linux/libmlx_Linux.a

DIR = srcs
SRCS_RAW = trie.c check.c files.c index.c instruction.c list.c main2.c  utils.c utils2.c instruction2.c instruction3.c 
SRCS = $(addprefix $(DIR)/,$(SRCS_RAW)) \

OBJS = $(SRCS:c=o)
INCLUDES = -I./includes -I./libft

LIBFT = libft.a

all: $(NAME)
$(NAME): libftcompile $(OBJS)
	$(CC) $(OBJS) $(DEBUG) -Llibft -l:libft.a -o $(NAME)
clean:
	rm $(OBJS) $(OBJB) -f
fclean: clean libftclean
	rm $(NAME) -f
re: fclean all
libftcompile:
	$(MAKE) -C libft
libftclean:
	$(MAKE) fclean -C libft

%.o: %.c def.h
	$(CC) -c $< -o $@ $(DEBUG) $(MINILIBX_FLAGS) $(CFLAGS) $(INCLUDES)