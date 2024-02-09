/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:47:55 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/08 18:36:12 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"

/**
 * @brief Structure for command args
 * Fill up this structure from parsing part
 * Use this structure from execution part
 * 
 * @param cmd - command, definitivly not NULL
 * @param args - list of arguments, NULLABLE
 * @param opts - list of options without hyphen (-), sorted by input order
 * @param red_in - input redirection file (<), NULLABLE
 * @param red_out - output redirection file (>), NULLABLE
 * @param red_in_delim - input redirection delimiter (<<), NULLABLE
 * @param red_out_append - output redirection file, append mode (>>), NULLABLE
 * @param envp - environment variables (from main)
 * @param next - next command pack, NULLABLE (BY REQUEST OF BFAISY ^^)
 */

typedef struct s_red
{
	t_list				*red_in; // mettre le fichier dedans
	t_list				*red_out; // mettre le fichier dedans
	t_list				*red_in_delim; // mettre la chose apres les << sinon NULL
	t_list				*red_out_append; // mettre le fichier dedans sinon NULL
}	t_red;

typedef struct s_cmd_args
{
	char				*cmd;
	t_list				*args;
	t_list				*opts;
	t_red				redirect;
	char				**envp;
	struct s_cmd_args	*next;
}	t_cmd_args;

#endif