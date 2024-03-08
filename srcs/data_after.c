/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_after.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:38:41 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/08 20:50:42 by bfaisy           ###   ########.fr       */
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
		{
			data = data_custom(stock, head, data);
						// printf("%d\n", data.i);
		}
		else if (stock->str[data.i] == ' ')
			return (data_afterv3(data, head, stock->str, false));
		else if (stock->str[data.i] == '|' && data.str != NULL)
			return (data_afterv2(&data, &head), data);
		else if (stock->str[data.i] == '|')
			return (ft_putstr_fd
				("bash: syntax error near\nunexpected token `|'\n", 2),
				data.i = -100, g_status = 2, stock->cond = false, data);
		else
			data.str = concatenation(data.str, stock->str[data.i]);
		data.i++;
	}
	return (data);
}

void	data_afterv2(t_string_and_i *data, t_cmd_args **head)
{
	(*data).i++;
	(*head)->is_pipe = 1;
}

t_string_and_i	data_afterv3(t_string_and_i	data, t_cmd_args *head, char *str, bool cond_add)
{
	while (str[data.i] == ' ')
	{
		data.i++;
		if (str[data.i] == '|')
			return (data_afterv2(&data, &head), data);
	}
	// printf("%sf\n", data.str);
		// printf("%cf\n", str[data.i]);
		// printf("%sdsf\n", data.str);

	// if (cond_add == false)
	// {
	// 	data.i--;
	// }
	(void)cond_add;
	// if (cond_add == true)
	// 	data.i++;
	// data.str = transform_str_quote(data.str); // a faire
	// printf("%sf\n", data.str);
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
		// printf("a\n");
		new_str = malloc(sizeof(char) * 2);
		if (!new_str)
			exit(1);
		new_str[0] = c;
		new_str[1] = '\0';
	}
	return (new_str);
}
