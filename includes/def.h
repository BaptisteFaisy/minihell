/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:16:39 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/10 20:06:58 by lhojoon          ###   ########.fr       */
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

// Defs : errors
# define ERR_MALLOC "Malloc error"
# define ERR_ACCESS "Permission denied"
# define ERR_NOENT "No such file or directory"
# define ERR_OPEN "Cannot open file"
# define ERR_UNKNOWN "Unknown error"

// Includes
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <term.h>
# include <stdbool.h>
# include "struct.h"

// Prototypes

// Parsing part
int			redirect(char *str, int i, t_red redirect);
int			create_firstnode_and_put(t_list *head, char *data);
int			create_node_and_put(t_list *head, char *data);
int			parsing(char *str, char **ev);
t_cmd_args	*create_node_cmd(t_cmd_args *head);
char		*data_after(char *str, int i);
int			find_next_pipe(char *str, int i);

// Execution part
int			execution(t_cmd_args *cmd_args);
bool		init_redirect_files(t_cmd_args *cargs, t_exec_info *info);

#endif
