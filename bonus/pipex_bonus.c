/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:45:59 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/20 20:55:55 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


void	child_process(t_pipex *s_pipex, char *envp[], int child_nr)
{
	char	*path;
	t_cmd	*right_cmd_node;

	if (s_pipex->forks == 1)
	{
		close(s_pipex->pipes[0][0]);
		close(s_pipex->pipes[0][1]);
		close(s_pipex->pipes[1][0]);
		close(s_pipex->pipes[1][1]);
		redirect(s_pipex->infile, s_pipex->outfile);
	}
	else if (child_nr == 1)
	{
		close(s_pipex->outfile);
		close(s_pipex->pipes[0][0]);
		close(s_pipex->pipes[1][0]);
		close(s_pipex->pipes[1][1]);
		if (s_pipex->infile < 0)
			infile_error(s_pipex);
		if (s_pipex->here_doc == 1)
			here_doc(s_pipex, s_pipex->pipes[0][1]);
		redirect(s_pipex->infile, s_pipex->pipes[0][1]);
	}
	else if (child_nr == s_pipex->forks)
	{
		close(s_pipex->infile);
		if (child_nr % 2 == 0)
		{
			close(s_pipex->pipes[0][1]);
			close(s_pipex->pipes[1][0]);
			close(s_pipex->pipes[1][1]);
			// ft_putendl_fd("final_paaris", STDOUT_FILENO);
			// ft_putnbr_fd(s_pipex->outfile, STDOUT_FILENO);
			redirect(s_pipex->pipes[0][0], s_pipex->outfile);
		}
		else
		{
			close(s_pipex->pipes[1][1]);
			close(s_pipex->pipes[0][0]);
			close(s_pipex->pipes[0][1]);
			// ft_putendl_fd("final_paaritu", STDOUT_FILENO);
			redirect(s_pipex->pipes[1][0], s_pipex->outfile);
		}
	}
	else
	{
		close(s_pipex->infile);
		close(s_pipex->outfile);
		if (child_nr % 2 == 0)
		{
			close(s_pipex->pipes[0][1]);
			close(s_pipex->pipes[1][0]);
			// ft_putendl_fd("second", STDOUT_FILENO);
			redirect(s_pipex->pipes[0][0], s_pipex->pipes[1][1]);
		}
		else
		{
			close(s_pipex->pipes[0][0]);
			close(s_pipex->pipes[1][1]);
			// ft_putendl_fd("third", STDOUT_FILENO);
			redirect(s_pipex->pipes[1][0], s_pipex->pipes[0][1]);
		}
	}
	right_cmd_node = get_node(s_pipex->s_cmd_lst, child_nr);
	// ft_putendl_fd(right_cmd_node->cmd, STDERR_FILENO);
	path = get_right_path(right_cmd_node->cmd, s_pipex->envp_pths);
	// ft_putendl_fd(path, STDERR_FILENO);
	if (!path)
		path_error(s_pipex, 127, right_cmd_node->cmd);
	else if (access(path, X_OK) != 0)
		path_error(s_pipex, 126, right_cmd_node->cmd);
	execve(path, right_cmd_node->args, envp);
	execve_error(s_pipex);
}

int	pipex(t_pipex *s_pipex, char *envp[])
{
	int		i;

	if (pipe(s_pipex->pipes[0]) == -1)
	{
		perror("Pipe error");
		return (2);
	}
	if (pipe(s_pipex->pipes[1]) == -1)
	{
		perror("Pipe error");
		return (2);
	}
	i = 0;
	while (i <= s_pipex->forks - 1)
	{
		s_pipex->pids[i] = fork();
		if (s_pipex->pids[i] == -1)
		{
			perror("Fork error");
			return (3);
		}
		if (s_pipex->pids[i] == 0)
			child_process(s_pipex, envp, (i + 1));
		i++;
	}
	close_all(s_pipex);
	ft_waiting(s_pipex->pids, s_pipex->forks);
	return (0);
}
