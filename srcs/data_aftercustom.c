/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_aftercustom.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:52:52 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/11 18:55:48 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	data_custom_init(bool *cond_add, bool *cond_quote,
		t_string_and_i *data, t_storage *stock)
{
	*cond_add = false;
	if (stock->str[(data)->i] == '\'')
		*cond_quote = true;
	else if (stock->str[(data)->i] == '"')
		*cond_quote = false;
	(data)->i++;
}

t_string_and_i	data_custom(t_storage *stock, t_cmd_args *head,
			t_string_and_i data)
{
	bool	cond_quote;
	bool	cond_add;

	data_custom_init(&cond_add, &cond_quote, &data, stock);
	while (stock->str[data.i])
	{
		if (stock->str[data.i] == '\'' && cond_quote == true)
			return (data_afterv3(data, head, stock->str, cond_add));
		else if (stock->str[data.i] == '"' && cond_quote == false)
			return (data_afterv3(data, head, stock->str, cond_add));
		else
		{
			data.str = concatenation(data.str, stock->str[data.i]);
			cond_add = true;
		}
		data.i++;
	}
	return (data);
}
