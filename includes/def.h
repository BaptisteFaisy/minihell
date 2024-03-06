/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:16:39 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/06 23:28:07 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

// Defs
# define PIPE 5
# define TRUE 1
# define FALSE 0
# define SHELL_NAME "bash"
# define F_SKIP_NUL 64

// Defs : errors
# define ERR_MALLOC "Malloc error"
# define ERR_PIPE "Pipe error"
# define ERR_OPEN "Cannot open file"
# define ERR_UNKNOWN "Unknown error"
# define ERR_GETCWD "Cannot get current working directory"
# define ERR_FORK "Fork error"
# define ERR_TOO_MANY_ARGS "too many arguments"
# define ERR_CMD_NOT_FOUND "command not found"
# define ERR_IS_DIR "Is a directory"
# define ERR_NUMERIC_REQUIRED "numeric argument required"

// Defs : Exit codes
# define EXEC_SUCCESS 0
# define EXEC_FAILURE 1
# define EXEC_INVLD_USAGE 2
# define EXEC_IS_DIR 126
# define EXEC_CMD_NFD 127

// Defs : redirect type
# define RED_IN 0
# define RED_OUT 1
# define RED_IN_DELIM 2
# define RED_OUT_APPEND 3

// Includes
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <term.h>
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"

extern int	g_status;

int				redirect(int i, t_red *redirect,
					t_cmd_args *head, t_storage *stock);
void			create_firstnode_and_put(t_list **head, char *data);
int				create_node_and_put(t_list **head, char *data);
int				parsing(char *str, t_list *ev);
t_cmd_args		*create_node_cmd(t_cmd_args **head, t_list *ev);
t_string_and_i	data_after(char *str, int i, t_cmd_args *head, bool *cond);
int				find_next_pipe(char *str, int i);
char			*transform_str(char *str);
void			freered(t_red redirect);
void			freelist(t_list *head);
void			freeheadcmd(t_cmd_args *head);
void			create_redirect_node_main(t_cmd_args *head);
void			create_redirect_node(t_red *head);
t_red			*get_last_redirect_node(t_red *head);
t_cmd_args		*create_next_node_head(t_cmd_args *head, t_list *ev);
int				check_test(char *str, bool *cond);
int				skipspace(char *str, int i);
t_string_and_i	data_after2(char *str, int i);
char			*transform_str_env(char *str, t_list *ev,
					t_storage *stock);
char			*transform_str_quote(char *str, bool cond2);
char			*transform_str_env2(char *str, t_list *ev,
					t_storage *storage, t_string_and_i stock);
char			*replacestr(char *strev, char *str, int cond);
int				compare(char *strev, char *str2, int i);
char			*replacestr2(char *newstr, int *k, int *i);
char			*replacestr3(char *str, char *strev, char *newstr,
					t_indice *indi);
char			*replacestr4(char *newstr, char *str, t_indice *indi);
char			*readline_str(char *prompt);

// Execution part
int				execution(t_cmd_args *cmd_args);
int				init_redirect_files(t_cmd_args *cargs, t_exec_info *info);
t_exec_info		*init_t_exec_info(void);
char			**resolve_path(t_list *envp);
int				redirect_open(char *path, int access_flag, int open_flag);
bool			is_builtin(char *cmd);
char			*get_cmd(t_cmd_args *cargs, t_exec_info *info);
int				get_file_by_prompt_delim(char *delim);
int				iter_exec(t_cmd_args *cargs, char **paths);
char			*get_env_var(t_list *envp, char *varname);
t_red_info		convert_red_info(t_red *raw);
int				set_exec_info(
					t_exec_info **info, char *cmd,
					t_cmd_args *cargs, char **paths);
void			print_final_output(int ifd);
void			set_fd(int fdcontainer[2], int first, int next);
char			*search_env_var(t_list *envp, char *var);
void			free_redirect_fd_except_last(t_list *lst);
char			**transform_envp(t_list *envp);
t_list			*get_list_envp(char **envp);
int				builtin_echo(t_cmd_args *cargs, t_exec_info *info);
int				builtin_cd(t_cmd_args *cargs, t_exec_info *info);
int				builtin_pwd(t_cmd_args *cargs, t_exec_info *info);
int				builtin_export(t_cmd_args *cargs, t_exec_info *info);
int				builtin_unset(t_cmd_args *cargs, t_exec_info *info);
int				builtin_env(t_cmd_args *cargs, t_exec_info *info);
int				builtin_exit(t_cmd_args *cargs, t_exec_info *info);
int				exec_builtin(t_cmd_args *cargs, t_exec_info *info);
char			**list_to_args(char *cmd, t_list *args);
void			closefd(int *fd);
int				get_input_fd(t_exec_info *info, int prevfd[2]);
int				get_output_fd(t_exec_info *info, int curfd[2]);
void			free_exec_info(t_exec_info *info);
void			close_two_fds(t_exec_info *info);
void			basherr(char *name, char *err);
bool			is_directory(char *path);
int				handle_execve(t_cmd_args *cargs, t_exec_info *info,
					char **envp_tmp, char **args_tmp);
void			signals(void);
void			sigquit_handler_process(int sig);
void			sigint_handler_process(int sig);
void			activate_sig_process(t_exec_info *info);
void			deactivate_sig_process(t_exec_info *info);

#endif