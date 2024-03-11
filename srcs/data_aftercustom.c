/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_aftercustom.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:52:52 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/11 16:51:49 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_string_and_i	data_custom(t_storage *stock, t_cmd_args *head,
			t_string_and_i data)
{
	bool	cond_quote;
	bool	cond_add;

	cond_add = false;
	if (stock->str[data.i] == '\'')
		cond_quote = true;
	else if (stock->str[data.i] == '"')
		cond_quote = false;
	data.i++;
	while (stock->str[data.i])
	{
		if (stock->str[data.i] == '\'' && cond_quote == true)
			return (data_afterv3(data, head, stock->str, cond_add));
		else if (stock->str[data.i] == '"' && cond_quote == false)
			return (data_afterv3(data, head, stock->str, cond_add));
		else if (stock->str[data.i] == '|' && data.str != NULL)
			return (data_afterv2(&data, &head, stock->str), data);
		else if (stock->str[data.i] == '|')
			return (ft_putstr_fd
				("bash: syntax error near\nunexpected token `|'\n", 2),
				data.i += 1, g_status = 2, stock->cond = false, data);
		else
		{
			data.str = concatenation(data.str, stock->str[data.i]);
			cond_add = true;
		}
		data.i++;
	}
	return (data);
}
