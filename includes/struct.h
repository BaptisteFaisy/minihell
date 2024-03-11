/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:47:55 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/11 17:35:53 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "def.h"
# include "libft.h"

typedef struct s_red_details
{
	char	*file;
	int		type;
}	t_red_details;

typedef struct s_red_info
{
	t_list	*red_in;
	t_list	*red_out;
}	t_red_info;

/**
 * @brief Structure for redirections 
 * 
 * @param red_in input redirection file or delimiter (<, <<), NULLABLE
 * @param red_out output redirection file (> , >>), NULLABLE
 * @param red_in_delim input redirection delimiter (<<), NULLABLE
 * @param red_out_delim output redirection file, append mode (>>), NULLABLE
 * @param next next element, NULLABLE
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
 * @param next next command pack, NULLABLE
 * @param exit_code exit code of exit cmd, if -1 do nothing, else exit with code
 */
typedef struct s_cmd_args
{
	char				*cmd;
	t_list				*args;
	t_list				*envp;
	t_red				*redirect;
	struct s_cmd_args	*next;
	int					is_first;
	int					is_pipe;
	int					cond;
	int					*exit_code;
	struct s_cmd_args	*head;
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
	t_red_info		redirect;
	char			**paths;
	char			*cmd;
	int				out_fd;
	int				in_fd;
	__sighandler_t	oldsint;
	__sighandler_t	oldsquit;
}	t_exec_info;

typedef struct s_storage
{
	char	*str;
	bool	cond;
	bool	cond2;
	bool	cond3;
	int		i;
	int		cond_env;
	bool	cond_is_alpha_dollar;
	bool	deja_malloc_boucle;
	bool	pipe2;
}t_storage;

typedef struct s_indice
{
	int		i;
	int		k;
	bool	cond_simple;
	bool	cond_double;
}t_indice;

#endif