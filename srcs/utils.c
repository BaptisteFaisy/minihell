/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:18:13 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/27 18:44:13 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	perror_return(char *str, int code)
{
	perror(str);
	return (code);
}

int	skipspace(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	return (i);
}
