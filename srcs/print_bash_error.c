/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bash_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:05:18 by lhojoon           #+#    #+#             */
/*   Updated: 2024/03/06 18:05:58 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	basherr(char *name, char *err)
{
	char	*str;

	if (err && name)
		str = ft_strjoin_many(5, SHELL_NAME, ": ", name, ": ", err);
	else if (name)
		str = ft_strjoin_many(3, SHELL_NAME, ": ", name);
	else if (err)
		str = ft_strjoin_many(3, SHELL_NAME, ": ", err);
	else
		return ;
	if (!str)
		ft_putendl_fd(ERR_MALLOC, 2);
	if (err)
		ft_putendl_fd(str, 2);
	else
		perror(str);
	free(str);
}
