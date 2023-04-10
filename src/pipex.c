/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:45:59 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/10 18:46:26 by tmarts           ###   ########.fr       */
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

int	first_cp(t_pipex *s_pipex)
{
	close(s_pipex->outfile);
	close(s_pipex->pp[0]);
	redirect(s_pipex->infile, s_pipex->pp[1]);
	execve("/bin/cat", NULL, NULL);
	return (0);
}

int	last_cp(t_pipex *s_pipex)
{
	close(s_pipex->infile);
	close(s_pipex->pp[1]);
	redirect(s_pipex->pp[0], s_pipex->outfile);
	execve("/bin/cat", NULL, NULL);
	return (0);
}

void	close_all(t_pipex *s_pipex)
{
	close(s_pipex->infile);
	close(s_pipex->outfile);
	close(s_pipex->pp[0]);
	close(s_pipex->pp[1]);
}

int	pipex(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	while (i++ < 1)
	{
		if (pipe(s_pipex->pp) == -1)
			perror("Pipe error");
	}
	i = 0;
	while (i < 2)
	{
		s_pipex->pids[i] = fork();
		if (s_pipex->pids[i] == -1)
			perror("Fork error");
		if (s_pipex->pids[i] == 0)
		{
			if (i == 0)
				return (first_cp(s_pipex));
			if (i == 1)
				return (last_cp(s_pipex));
		}
		i++;
	}
	close_all(s_pipex);
	i = 0;
	while (i++ < 2)
		wait(NULL);
	return (0);
}