/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_funcs_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 07:38:07 by nromito           #+#    #+#             */
/*   Updated: 2024/03/05 07:53:18 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_p(int *fd)
{
	if (*fd != -1)
	{
		if (close(*fd) == -1)
			ft_error(NULL, 11);
		*fd = -1;
	}
}

void	dup2_p(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		ft_error(NULL, 12);
}

void	wait_p(int *status)
{
	if (wait(status) == -1)
		ft_error(NULL, 13);
}

int	access_p(char *file, int mode)
{
	int	ret;

	ret = access(file, mode);
	if (ret == -1 && errno != ENOENT)
		ft_error(NULL, 14);
	return (ret);
}

void	close_fds(void)
{
	int	i;

	i = 0;
	while (i < 1024)
		close(i++);
}
