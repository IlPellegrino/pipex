/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_and_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:23:34 by nromito           #+#    #+#             */
/*   Updated: 2024/03/05 07:51:16 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_files(int argc, char **argv, t_pipex *pipex, bool is_heredoc)
{
	if (is_heredoc)
	{
		pipex->file_fds[0] = create_heredoc(argv[2]);
		pipex->file_fds[1] = open_p(argv[argc - 1], O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	}
	else
	{
		pipex->file_fds[0] = open_p(argv[1], O_RDONLY, 0644);
		pipex->file_fds[1] = open_p(argv[argc - 1], O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	}
}

bool	check_args(int argc, char **argv)
{
	if (argc < 5)
		ft_error("Wrong number of arguments", 10);
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		if (argc < 6)
			ft_error("Wrong number of arguments", 54);
		return (true);
	}
	return (false);
}

int	wait_for_commands(int n_cmds)
{
	int	status;
	int	i;

	i = 0;
	while (i < n_cmds)
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		i++;
	}
	return (status);
}

char	**get_path(char **envp)
{
	char	**path;

	while (envp && *envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = ft_split(*envp + 5, ':');
			return (path);
		}
		envp++;
	}
	ft_error("PATH not found in envp", 9);
	return (NULL);
}

char	*get_cmd_path(char *cmd_name, t_pipex *pipex)
{
	char	*tmp;
	char	*full_path;
	int		i;

	i = 0;
	while (pipex->path[i])
	{
		tmp = pipex->path[i];
		pipex->path[i] = ft_strjoin(pipex->path[i], "/");
		free(tmp);
		full_path = ft_strjoin(pipex->path[i], cmd_name);
		if (access_p(full_path, X_OK) == 0)
			return (full_path);
		free (full_path);
		i++;
	}
	ft_error(ft_strjoin("pipex: command not found: ", cmd_name), 127);
	return (NULL);
}
