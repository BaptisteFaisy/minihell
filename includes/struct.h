/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
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
 * @param cmd - command
 * @param args - list of arguments
 * @param opts - list of options without hyphen (-), sorted by input order
 * 
 * 
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