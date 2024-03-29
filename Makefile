NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

DIR = srcs
SRCS_RAW =	main.c \
			data_after.c \
			node.c \
			parsing.c \
			redirect.c \
			execution_main.c \
			utils.c \
			redirect_open.c \
			init_redirect_files.c \
			resolve_path.c \
			get_cmd.c \
			init_t_exec_info.c \
			transform_str.c \
            free.c \
			noderedirect.c \
			iter_exec.c \
			is_builtin.c \
			get_env_var.c \
			exec_builtin.c \
			convert_red_info.c \
			iter_exec_2.c \
			builtin_pwd.c \
			builtin_env.c \
			builtin_export.c \
			builtin_unset.c \
			builtin_cd.c \
			builtin_echo.c \
			list_to_args.c \
			transform_envp.c \
			search_env_var.c \
			checktest.c \
			iter_exec_3.c \
			free_exec_info.c \
			data_afterv2.c \
			transform_str_env.c \
			transform_str_quote.c \
			transform_str_env_utils.c \
			print_bash_error.c \
			is_directory.c \
			handle_execve.c \
			signals.c \
			readline_str.c \
			builtin_exit.c \
			parsing_2.c \
			iter_exec_4.c \
			data_aftercustom.c \
			quote.c \
			rm.c \
			builtin_export_2.c \
			transform_str_env2.c \
			node_2.c \
			signals_2.c
SRCS = $(addprefix $(DIR)/,$(SRCS_RAW)) \

OBJS = $(SRCS:c=o)
INCLUDES = -I./includes -I./libft 

DEBUG = -g3

LIBFT = libft/libft.a

all: $(NAME)
$(NAME): ${LIBFT} $(OBJS)
	$(CC) $(OBJS) $(DEBUG) $(INCLUDES) -o $(NAME) $(CFLAGS) -l:libft.a -Llibft -lreadline
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