/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:47:55 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/22 10:06:19 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "def.h"
# include "libft.h"

/**
 * @brief Structure for redirections 
 * 
 * @param red_in input redirection file (<), NULLABLE
 * @param red_out output redirection file (>), NULLABLE
 * @param red_in_delim input redirection delimiter (<<), NULLABLE
 * @param red_out_append output redirection file, append mode (>>), NULLABLE
*/
typedef struct s_red
{
	char			*red_in;
	char			*red_in_delim;
	char			*red_out;
	char			*red_out_delim;
	struct s_red	*next;
}	t_red;

/**
 * @brief Structure for command args
 * Fill up this structure from parsing part
 * Use this structure from execution part
 * 
 * @param cmd command, NULLABLE
 * @param args list of arguments, NULLABLE
 * @param opts list of options without hyphen (-), sorted by input order
 * @param redirect redirections
 * @param envp environment variables (from main)
 * @param next next command pack, NULLABLE (BY REQUEST OF BFAISY ^^)
 */
typedef struct s_cmd_args
{
	char				*cmd;
	t_list				*args;
	t_red				*redirect;
	char				**envp;
	struct s_cmd_args	*next;
	int					is_first;
	int					is_pipe;
}	t_cmd_args;

typedef struct s_string_and_i
{
	char	*str;
	int		i;
}	t_string_and_i;

/**
 * @brief Data storage for execution
 * 
 * @param redirect fds for redirection
 * @param paths envp paths
 * @param cmd executable cmd
*/
typedef struct s_exec_info
{
	t_red			redirect;
	char			**paths;
	char			*cmd;
}	t_exec_info;



# define RED_IN 0
#endif