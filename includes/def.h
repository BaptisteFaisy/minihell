/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   def.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:16:39 by bfaisy            #+#    #+#             */
/*   Updated: 2024/02/09 20:57:22 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEF_H
# define DEF_H

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
# include "struct.h"

int			redirect(char *str, int i, t_red redirect);
void		create_firstnode_and_put(t_list **head, char *data);
int			create_node_and_put(t_list **head, char *data);
int			parsing(char *str, char **ev);
t_cmd_args	*create_node_cmd(t_cmd_args *head, char **ev);
char		*data_after(char *str, int i);
int			find_next_pipe(char *str, int i);
char		*transform_str(char *str);

# define PIPE 5
# define TRUE 1
# define FALSE 0
#endif
