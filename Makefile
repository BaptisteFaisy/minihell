NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

DIR = srcs
SRCS_RAW = main.c
SRCS = $(addprefix $(DIR)/,$(SRCS_RAW)) \

OBJS = $(SRCS:c=o)
INCLUDES = -I./includes -I./libft

DEBUG = 

LIBFT = Libft/libft.a

all: $(NAME)
$(NAME): ${LIBFT} $(OBJS)
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
	$(CC) -c $< -o $@ $(DEBUG) $(CFLAGS) $(INCLUDES)