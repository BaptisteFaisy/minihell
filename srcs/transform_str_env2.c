/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_str_env2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:08:50 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/11 18:43:02 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	transform_env_suite(int i, t_str_pack *pack, t_list *ev,
		t_storage **storage)
{
	t_string_and_i	stock;

	stock = data_after2(pack->str, i);
	(*storage)->i = i;
	pack->str = transform_str_env2(pack->str, ev, *storage, stock);
	if ((*storage)->cond3 == 0)
		pack->str = rmstr(stock, pack->str, *storage);
	free(stock.str);
	(*storage)->cond_env = 1;
	(*storage)->i -= 2;
	return ((*storage)->i);
}

void	transform_env_initial(t_storage *storage, t_str_pack *pack,
		char *str)
{
	storage->deja_malloc_boucle = false;
	pack->str = str;
	pack->newstr = str;
}

bool	rmstr_suite(int *i, int *j, char *str, t_string_and_i stock)
{
	(*i)++;
	while (str[*i] == stock.str[*j])
	{
		(*i)++;
		(*j)++;
		if (str[*i] == '\0')
			return (false);
	}
	return (true);
}
