/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 20:38:23 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/10 21:08:05 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd(t_cmd_args *cargs)
{
	char	*tmp;
	char	*c;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		c = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(c, 0) == 0)
			return (c);
		free(c);
		paths++;
	}
	return (NULL);
}
