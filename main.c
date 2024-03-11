/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 08:00:05 by nromito           #+#    #+#             */
/*   Updated: 2024/03/05 07:54:13 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	bool	is_heredoc;
	t_pipex	pipex;
	int		status;

	if (argc != 5)
		ft_error("Wrong number of arguments", 10);
	else
	{
		is_heredoc = check_args(argc, argv);
		pipex.path = get_path(envp);
		open_files(argc, argv, &pipex, is_heredoc);
		pipex.n_cmds = argc - 3 - is_heredoc;
		pipex.n_pipes = pipex.n_cmds - 1;
		launch_commands(argv + 2 + is_heredoc, envp, &pipex);
		status = wait_for_commands(pipex.n_cmds);
		free_matrix(pipex.path);
		close_fds();
		exit(status);
	}
}
