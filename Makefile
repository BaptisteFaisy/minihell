NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

DIR = srcs
SRCS_RAW = main.c data_after.c node.c parsing.c redirect.c transform_str.c
SRCS = $(addprefix $(DIR)/,$(SRCS_RAW)) \

OBJS = $(SRCS:c=o)
INCLUDES = -I./includes -I./libft 

DEBUG = 

LIBFT = libft/libft.a

all: $(NAME)
$(NAME): ${LIBFT} $(OBJS)
	$(CC) $(OBJS) $(DEBUG) $(INCLUDES) -o $(NAME) -l:libft.a -Llibft 
clean:
	rm $(OBJS) $(OBJB) -f
fclean: clean libftclean
	rm $(NAME) -f
re: fclean all
libftclean:
	$(MAKE) fclean -C libft

${LIBFT}:
	$(MAKE) -C libft

%.o: %.c
	$(CC) -c $< -o $@ $(DEBUG) $(CFLAGS) $(INCLUDES)