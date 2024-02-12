/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhojoon <lhojoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 18:27:50 by lhojoon           #+#    #+#             */
/*   Updated: 2024/02/12 19:23:28 by lhojoon          ###   ########.fr       */
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
	if (errno == EACCES)
		print_error(path, ERR_ACCESS);
	else if (errno == ENOENT)
		print_error(path, ERR_NOENT);
	else
		print_error(path, ERR_UNKNOWN);
	return (false);
}

/**
 * @brief Open file for redirection
 * @param path path to file
 * @param access_flag access flag, refer : https://shorturl.at/bflq8
 * @param open_flag open flag, refer : https://shorturl.at/fwPWY
 * @return int File descriptor, -1 when error
 * -1 When Error
*/
int	redirect_open(char *path, int access_flag, int open_flag)
{
	int	fd;

	if (!access_file(path, access_flag))
		return (-1);
	fd = open(path, open_flag, S_IRWXU);
	if (fd < 0)
		return (print_error(path, ERR_OPEN), -1);
	return (fd);
}
