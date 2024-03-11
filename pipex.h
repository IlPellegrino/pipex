/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nromito <nromito@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 18:21:58 by nromito           #+#    #+#             */
/*   Updated: 2024/03/05 07:50:49 by nromito          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <errno.h>
# include "get_next_line.h"
# include "libft/libft.h"

typedef struct s_pipex
{
	int		file_fds[2];
	int		pipe_fds[2];
	int		prev_output_fd;
	char	**path;
	int		n_cmds;
	int		n_pipes;
}	t_pipex;

//cheks_&_paths.c
bool		check_args(int argc, char **argv);
void		open_files(int argc, char **argv, t_pipex *pipex, bool is_heredoc);
int			wait_for_commands(int n_cmds);
char		**get_path(char **envp);
char		*get_cmd_path(char *cmd_name, t_pipex *pipex);
//pipex.c
void		launch_commands(char **argv, char **envp, t_pipex *pipex);
int			parent(t_pipex *pipex, bool is_last);
void		child(char *cmd_line, char **envp, t_pipex *pipex, bool is_last);
int			create_heredoc(char *limiter);
//protected functions
void		execve_p(char *cmd, char **argv, char **envp);
void		pipe_p(int pipe_fds[2]);
int			fork_p(void);
void		ft_error(char *msg, int id);
int			open_p(char *file, int flags, int mode);
void		close_p(int *fd);
void		dup2_p(int old_fd, int new_fd);
void		wait_p(int *status);
int			access_p(char *file, int mode);
const char	**free_matrix(char **matrix);
void		close_fds(void);

#endif