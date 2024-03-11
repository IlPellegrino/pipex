/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:18:35 by nromito           #+#    #+#             */
/*   Updated: 2024/03/06 09:00:19 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	launch_commands(char **argv, char **envp, t_pipex *pipex)
{
	int			i;
	pid_t		pid;

	pipex->prev_output_fd = pipex->file_fds[0];
	i = 0;
	while (i < pipex->n_cmds)
	{
		if (i < pipex->n_pipes)
			pipe_p(pipex->pipe_fds);
		pid = fork_p();
		if (pid == 0)
			child(argv[i], envp, pipex, i == (pipex->n_cmds -1));
		else
			pipex->prev_output_fd = parent(pipex, i == (pipex->n_cmds - 1));
		i++;
	}
}

int	parent(t_pipex *pipex, bool is_last)
{
	if (is_last == false)
		close_p(&pipex->pipe_fds[1]);
	else
		close_p(&pipex->file_fds[1]);
	close_p(&pipex->prev_output_fd);
	return (pipex->pipe_fds[0]);
}

void	child(char *cmd_line, char **envp, t_pipex *pipex, bool is_last)
{
	char	**cmd_args;
	char	*cmd_path;

	if (is_last == false)
		close_p(&pipex->pipe_fds[0]);
	dup2_p(pipex->prev_output_fd, STDIN_FILENO);
	close_p(&pipex->prev_output_fd);
	if (is_last == false)
	{
		dup2_p(pipex->pipe_fds[1], STDOUT_FILENO);
		close_p(&pipex->pipe_fds[1]);
	}
	else
	{
		dup2_p(pipex->file_fds[1], STDOUT_FILENO);
		close_p(&pipex->file_fds[1]);
	}
	cmd_args = ft_split(cmd_line, ' ');
	cmd_path = get_cmd_path(cmd_args[0], pipex);
	execve_p(cmd_path, cmd_args, envp);
	close_fds();
}

int	create_heredoc(char *limiter)
{
	int		heredoc_fd;
	char	*line;
	int		len;

	heredoc_fd = open_p("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		len = ft_strlen(line);
		line[len - 1] = '\0';
		if (ft_strncmp(line, limiter, len) == 0)
			break ;
		ft_putstr_fd(line, heredoc_fd);
		ft_putstr_fd("\n", heredoc_fd);
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
	get_next_line(-1);
	close_p(&heredoc_fd);
	heredoc_fd = open_p("heredoc", O_RDONLY, 0644);
	return (heredoc_fd);
}

const char	**free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
	return (NULL);
}
