/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:13:01 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 17:48:28 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *cmd)
{
	char	**builtins;

	builtins = ft_split("echo cd pwd export unset env exit", ' ');
	if (!builtins)
		return (false);
	while (*builtins)
	{
		if (ft_strncmp(cmd, *builtins, ft_strlen(*builtins)))
		{
			ft_freesplit(builtins);
			return (true);
		}
		builtins++;
	}
	ft_freesplit(builtins);
	return (false);
}
