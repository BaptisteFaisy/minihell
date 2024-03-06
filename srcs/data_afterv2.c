/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_afterv2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfaisy <bfaisy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:12:03 by bfaisy            #+#    #+#             */
/*   Updated: 2024/03/06 16:46:16 by bfaisy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "def.h"

char			*concatenation2(char *str, char c);
void			data_afterv22(t_string_and_i *data, t_cmd_args **head);
t_string_and_i	data_afterv32(t_string_and_i	data, t_cmd_args *head, char *str);

t_string_and_i	data_after2(char *str, int i, t_cmd_args *head, bool *cond)
{
	t_string_and_i	data;

	data.str = NULL;
	data.i = i;
	while (str[data.i] == ' ' || str[data.i] == '<' || str[data.i] == '>'
		|| str[data.i] == '!')
		data.i++;
	if (str[data.i] == '\n')
		return (data);
	while (str[data.i])
	{
		if (str[data.i] == ' ' || str[data.i] == '"')
			return (data_afterv32(data, head, str));
		else if (str[data.i] == '|' && data.str != NULL)
			return (data_afterv22(&data, &head), data);
		else if (str[data.i] == '|')
			return (ft_putstr_fd
				("bash: syntax error near\nunexpected token `|'\n", 2),
				data.i = -100, g_status = 2, *cond = false, data);
		else
			data.str = concatenation2(data.str, str[data.i]);
		data.i++;
	}
	return (data);
}

void	data_afterv22(t_string_and_i *data, t_cmd_args **head)
{
	(*data).i++;
	(*head)->is_pipe = 1;
}

t_string_and_i	data_afterv32(t_string_and_i	data, t_cmd_args *head, char *str)
{
	while (str[data.i] == ' ')
	{
		data.i++;
		if (str[data.i] == '|')
			return (data_afterv22(&data, &head), data);
	}
	return (data);
}

// int	find_next_pipe2(char *str, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '|')
// 			return (j + 1);
// 		j++;
// 		i++;
// 	}
// 	return (0);
// }

char	*concatenation2(char *str, char c)
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
