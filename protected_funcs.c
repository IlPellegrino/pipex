/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_funcs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:37:31 by nromito           #+#    #+#             */
/*   Updated: 2024/03/04 16:28:21 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execve_p(char *cmd_path, char **argv, char **envp)
{
	if (execve(cmd_path, argv, envp) == -1)
		ft_error(NULL, 15);
}

void	pipe_p(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
		ft_error(NULL, 27);
}

int	fork_p(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_error(NULL, 32);
	return (pid);
}

void	ft_error(char *msg, int id)
{
	if (!msg)
		perror("Error");
	else
	{
		ft_putstr_fd("Error: ", STDERR_FILENO);
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	close_fds();
	if (id == 127)
		free(msg);
	exit(id);
}

int	open_p(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd == -1)
		ft_error(NULL, 10);
	return (fd);
}
