/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:45:59 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/18 23:17:59 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect(int in_fd, int out_fd)
{
	dup2(in_fd, STDIN_FILENO);
	close(in_fd);
	dup2(out_fd, STDOUT_FILENO);
	close(out_fd);
}

void	close_all(t_pipex *s_pipex)
{
	close(s_pipex->infile);
	close(s_pipex->outfile);
	close(s_pipex->pp[0]);
	close(s_pipex->pp[1]);
}

static void	ft_waiting(int *pids)
{
	t_wait	s_wait;

	waitpid(pids[0], &s_wait.wstatus, 0);
	waitpid(pids[1], &s_wait.wstatus2, 0);
	if (WIFEXITED(s_wait.wstatus2))
	{
		s_wait.status_code = 0;
		s_wait.status_code = WEXITSTATUS(s_wait.wstatus2);
		if (s_wait.status_code != 0)
			exit(s_wait.status_code);
	}
}

void	child(t_pipex *s_pipex, char *envp[], int child_nr)
{
	char	*path;

	if (child_nr == 0)
	{
		close(s_pipex->outfile);
		close(s_pipex->pp[0]);
		if (s_pipex->infile < 0)
			infile_error(s_pipex);
		redirect(s_pipex->infile, s_pipex->pp[1]);
	}
	else if (child_nr == 1)
	{
		close(s_pipex->infile);
		close(s_pipex->pp[1]);
		redirect(s_pipex->pp[0], s_pipex->outfile);
	}
	path = get_right_path(s_pipex->exec[child_nr].cmd, s_pipex->envp_pths);
	if (!path)
		path_error(s_pipex, 127, s_pipex->exec[child_nr].cmd);
	else if (access(path, X_OK) != 0)
		path_error(s_pipex, 126, s_pipex->exec[child_nr].cmd);
	execve(path, s_pipex->exec[child_nr].args, envp);
	ft_putendl_fd("pipex: execve error: ", STDERR_FILENO);
	pipex_free(s_pipex);
	exit(EXIT_FAILURE);
}

int	pipex(t_pipex *s_pipex, char *envp[])
{
	int		i;

	if (pipe(s_pipex->pp) == -1)
	{
		perror("Pipe error");
		return (2);
	}
	i = 0;
	while (i < 2)
	{
		s_pipex->pids[i] = fork();
		if (s_pipex->pids[i] == -1)
		{
			perror("Fork error");
			return (3);
		}
		if (s_pipex->pids[i] == 0)
			child(s_pipex, envp, i);
		i++;
	}
	close_all(s_pipex);
	ft_waiting(s_pipex->pids);
	return (0);
}
