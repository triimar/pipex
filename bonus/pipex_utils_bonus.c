/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:40:52 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/21 18:09:19 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	make_pipes(int pipe1[2], int pipe2[2])
{
	if (pipe(pipe1) == -1)
		return (2);
	if (pipe(pipe2) == -1)
		return (2);
	return (0);
}

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
	close(s_pipex->pipe1[0]);
	close(s_pipex->pipe1[1]);
	close(s_pipex->pipe2[0]);
	close(s_pipex->pipe2[1]);
}

t_cmd	*get_node(t_cmd *list, int child_nr)
{
	t_cmd	*current;
	int		i;

	i = 1;
	current = list;
	if (child_nr == 1)
		return (current);
	while (current && i < child_nr)
	{
		current = current->next;
		i++;
	}	
	return (current);
}

void	ft_waiting(int *pids, int nr_of_forks)
{
	t_wait	s_wait;
	int		pid_index;

	pid_index = 0;
	while (pid_index < nr_of_forks)
	{
		waitpid(pids[pid_index], &s_wait.wstatus, 0);
		pid_index++;
	}
	if (WIFEXITED(s_wait.wstatus))
	{
		s_wait.status_code = 0;
		s_wait.status_code = WEXITSTATUS(s_wait.wstatus);
		if (s_wait.status_code != 0)
			exit(s_wait.status_code);
	}
}
