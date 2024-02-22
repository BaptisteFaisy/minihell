/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:16:39 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/22 10:33:35 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

// Defs
# define PIPE 5
# define TRUE 1
# define FALSE 0
# define EXEC_SUCCESS 0
# define EXEC_FAILURE 1
# define SHELL_NAME "bash"
# define F_SKIP_NUL 64

// Defs : errors
# define ERR_MALLOC "Malloc error"
# define ERR_OPEN "Cannot open file"
# define ERR_UNKNOWN "Unknown error"
# define ERR_GETCWD "Cannot get current working directory"
# define ERR_FORK "Fork error"
# define ERR_CD_TOO_MANY_ARGS "too many arguments"

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
# include "struct.h"

int	g_status = 0;
int				redirect(char *str, int i, t_red *redirect, t_cmd_args *head);
void			create_firstnode_and_put(t_list **head, char *data);
int				create_node_and_put(t_list **head, char *data);
int				parsing(char *str, char **ev);
t_cmd_args		*create_node_cmd(t_cmd_args **head, char **ev);
t_string_and_i	data_after(char *str, int i, t_cmd_args *head);
int				find_next_pipe(char *str, int i);
char			*transform_str(char *str);
void			freered(t_red redirect);
void			freelist(t_list *head);
void			freeheadcmd(t_cmd_args *head);
void 			create_redirect_node_main(t_cmd_args *head);
void			create_redirect_node(t_red *head);
t_red			*get_last_redirect_node(t_red *head);
t_cmd_args		*create_next_node_head(t_cmd_args *head, char **ev);



// Execution part
int				execution(t_cmd_args *cmd_args);
bool			init_redirect_files(t_cmd_args *cargs, t_exec_info *info);
t_exec_info		*init_t_exec_info(void);
char			**resolve_path(t_list *envp);
int				redirect_open(char *path, int access_flag, int open_flag);
bool			is_builtin(char *cmd);
char			*get_cmd(t_cmd_args *cargs, t_exec_info *info);
int				get_file_by_prompt_delim(char *delim);
int				iter_exec(t_cmd_args *cargs, char **paths);
char			*get_env_var(t_list *envp, char *varname);
t_red_info		convert_red_info(t_red *raw);
bool			set_exec_info(
					t_exec_info **info, char *cmd,
					t_cmd_args *cargs, char **paths);
void			print_final_output(int ifd);
void			set_fd(int fdcontainer[2], int first, int next);
void			free_redirect(void *content);
bool			add_pid(t_list **pids, pid_t pid);
int				wait_pid(t_list **pids);
t_list			*search_env_var(t_list *envp, char *var);
char			**transform_envp(t_list *envp);
t_list			*get_list_envp(char **envp);
void			builtin_echo(t_cmd_args *cargs, t_exec_info *info);
void			builtin_cd(t_cmd_args *cargs, t_exec_info *info);
void			builtin_pwd(t_cmd_args *cargs, t_exec_info *info);
void			builtin_export(t_cmd_args *cargs, t_exec_info *info);
void			builtin_unset(t_cmd_args *cargs, t_exec_info *info);
void			builtin_env(t_cmd_args *cargs, t_exec_info *info);
void			exec_builtin(t_cmd_args *cargs, t_exec_info *info);

#endif
