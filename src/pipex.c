/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:45:59 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/12 23:12:18 by tmarts           ###   ########.fr       */
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

int	child_process(t_pipex *s_pipex, char *envp[], int fork_nr)
{
	char	*path;

	if (fork_nr == 0)
	{
		close(s_pipex->outfile);
		close(s_pipex->pp[0]);
		redirect(s_pipex->infile, s_pipex->pp[1]);
	}
	else if (fork_nr == 1)
	{
		close(s_pipex->infile);
		close(s_pipex->pp[1]);
		redirect(s_pipex->pp[0], s_pipex->outfile);
	}
	path = get_right_path(s_pipex->exec[fork_nr].arguments[0], s_pipex->envp_paths);
	if (!path)
	{
		ft_putstr_fd("PIPEX: command not found: ", 2);
		ft_putendl_fd(s_pipex->exec[fork_nr].cmd, 2);
		exit(127);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("PIPEX: command not executable: ", 2);
		ft_putendl_fd(s_pipex->exec[fork_nr].cmd, 2);
		exit(126);
	}
	execve(path, s_pipex->exec[fork_nr].arguments, envp);
	perror("execve failure");
	return (1);
}

void	close_all(t_pipex *s_pipex)
{
	close(s_pipex->infile);
	close(s_pipex->outfile);
	close(s_pipex->pp[0]);
	close(s_pipex->pp[1]);
}

int	pipex(t_pipex *s_pipex, char *envp[])
{
	int	i;
	// int status;

	if (pipe(s_pipex->pp) == -1)
	{
		perror("Pipe error");
		return (1);
	}
	i = 0;
	while (i < 2)
	{
		s_pipex->pids[i] = fork();
		if (s_pipex->pids[i] == -1)
		{
			perror("Fork error");
			return (2);
		}
		if (s_pipex->pids[i] == 0)
			child_process(s_pipex, envp, i);
		i++;
	}
	close_all(s_pipex);
	i = 0;
	int wstatus;
	while (i++ < 2)
	{
		wait(&wstatus);
		if (WIFEXITED(wstatus)) // if returns "true" then normal termination happened
		{
			int statusCode = WEXITSTATUS(wstatus);
			if (statusCode != 0)
				exit(statusCode);
		}
	}	
	// while (i++ < 2)
	// 	wait(NULL);
	return (0);
}
