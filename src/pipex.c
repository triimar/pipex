/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:45:59 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/13 22:58:47 by tmarts           ###   ########.fr       */
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
	// char	*path;

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
	// path = get_right_path(s_pipex->exec[fork_nr].arguments[0], s_pipex->envp_paths);
	// if (!path)
	// {
	// 	ft_putstr_fd("pipex: command not found: ", 2);
	// 	ft_putendl_fd(s_pipex->exec[fork_nr].arguments[0], 2);
	// 	exit(127);
	// }
	// else if (access(path, X_OK) != 0)
	// {
	// 	ft_putstr_fd("pipex: command not executable: ", 2);
	// 	ft_putendl_fd(s_pipex->exec[fork_nr].arguments[0], 2);
	// 	exit(126);
	// }
	execve(s_pipex->exec[fork_nr].path, s_pipex->exec[fork_nr].arguments, envp);
	ft_putendl_fd("pipex: execve error: ", 2);
	exit(EXIT_FAILURE);
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
		{		
			child_process(s_pipex, envp, i);
			// exit(EXIT_FAILURE);
		}
		i++;
	}
	close_all(s_pipex);
	int wstatus;
	int wstatus2;
	waitpid(s_pipex->pids[0], &wstatus, 0);
	waitpid(s_pipex->pids[1], &wstatus2, 0);
	int statusCode = 0;
	if (WIFEXITED(wstatus)) // if returns "true" then normal termination happened
	{
		statusCode = WEXITSTATUS(wstatus2);
		if (statusCode != 0)
		{
			exit(statusCode);
		}
	}
	return(0);
}
