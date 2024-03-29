/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_after.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:38:41 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/17 19:33:39 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

t_string_and_i	data_after(t_storage *stock, int i, t_cmd_args *head)
{
	t_string_and_i	data;

	data.str = NULL;
	data.i = i;
	while (stock->str[data.i] == ' ' || stock->str[data.i] == '<'
		|| stock->str[data.i] == '>' || stock->str[data.i] == '!')
		data.i++;
	while (stock->str[data.i])
	{
		if (stock->str[data.i] == '\'' || stock->str[data.i] == '"')
			data = data_custom(stock, head, data);
		else if (stock->str[data.i] == ' '
			|| stock->str[data.i] == '>' || stock->str[data.i] == '<')
			return (data_afterv3(data, head, stock->str, false));
		else if (stock->str[data.i] == '|' && head->cmd == NULL)
			return (ft_putstr_fd
				("bash: syntax error near\nunexpected token '|'\n", 2),
				data.i += 1, g_status = 2, stock->cond = false, data);
		else if (stock->str[data.i] == '|')
			return (data_afterv2(&data, &head, stock->str), data);
		else
			data.str = concatenation(data.str, stock->str[data.i]);
		data.i++;
	}
	return (data);
}

void	data_afterv2(t_string_and_i *data, t_cmd_args **head, char *str)
{
	data->i++;
	while (str[data->i] == ' ')
		data->i++;
	(*head)->is_pipe = 1;
}

t_string_and_i	data_afterv3(t_string_and_i	data, t_cmd_args *head, char *str,
			bool cond_add)
{
	while (str[data.i] == ' ')
		data.i++;
	(void)head;
	(void)cond_add;
	return (data);
}

int	find_next_pipe(char *str, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (j + 1);
		j++;
		i++;
	}
	return (0);
}

char	*concatenation(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	if (str)
	{
		new_str = malloc(sizeof(char) * (ft_strlen(str) + 2));
		if (!new_str)
			exit (1);
		ft_strlcpy(new_str, str, ft_strlen(str) + 2);
		while (str[i])
			i++;
		new_str[i] = c;
		new_str[i + 1] = '\0';
		free(str);
	}
	else
	{
		new_str = malloc(sizeof(char) * 2);
		if (!new_str)
			exit(1);
		new_str[0] = c;
		new_str[1] = '\0';
	}
	return (new_str);
}
