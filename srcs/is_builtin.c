/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:13:01 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/07 18:04:20 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	char	**builtins;
	int		i;

	if (!cmd)
		return (false);
	builtins = ft_split("echo cd pwd export unset env exit", ' ');
	i = 0;
	if (!builtins)
		return (false);
	while (*(builtins + i))
	{
		if (ft_strncmp(cmd, *(builtins + i),
				ft_strlen(*(builtins + i)) + 1) == 0)
		{
			ft_freesplit(builtins);
			return (true);
		}
		i++;
	}
	ft_freesplit(builtins);
	return (false);
}
