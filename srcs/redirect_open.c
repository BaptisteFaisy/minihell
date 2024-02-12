/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:27:50 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 12:09:26 by lhojoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *path, char *err)
{
	char	*s;

	s = ft_strjoin_many(5, SHELL_NAME, ": ", path, ": ", err);
	perror(s);
	free(s);
}

// TODO : Verify all existing errors
static bool	access_file(char *path, int type)
{
	int	access_result;

	access_result = access(path, type);
	if (access_result == 0)
		return (true);
	if (access_result == EACCES)
		print_error(path, ERR_ACCESS);
	else if (access_result == ENOENT)
		print_error(path, ERR_NOENT);
	else
		print_error(path, ERR_UNKNOWN);
	return (false);
}

/**
 * @brief Open file for redirection
 * @param path - path to file
 * @param access_flag - access flag, refer : https://shorturl.at/bflq8
 * @param open_flag - open flag, refer : https://shorturl.at/fwPWY
 * @return int
 * -1 When Error
*/
int	redirect_open(char *path, int access_flag, int open_flag)
{
	int	fd;

	if (!access_file(path, access_flag))
		return (-1);
	fd = open(path, open_flag);
	if (fd < 0)
		return (print_error(path, ERR_OPEN), -1);
	return (fd);
}
