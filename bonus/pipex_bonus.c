/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:45:59 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/21 18:11:19 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_middle(t_pipex *s_pipex, int child_nr)
{
	close(s_pipex->infile);
	close(s_pipex->outfile);
	if (child_nr % 2 == 0)
	{
		close(s_pipex->pipe1[1]);
		close(s_pipex->pipe2[0]);
		redirect(s_pipex->pipe1[0], s_pipex->pipe2[1]);
	}
	else
	{
		close(s_pipex->pipe1[0]);
		close(s_pipex->pipe2[1]);
		redirect(s_pipex->pipe2[0], s_pipex->pipe1[1]);
	}
}

static void	child_first(t_pipex *s_pipex)
{
	if (s_pipex->forks == 1)
	{
		close(s_pipex->pipe1[0]);
		close(s_pipex->pipe1[1]);
		close(s_pipex->pipe2[0]);
		close(s_pipex->pipe2[1]);
		redirect(s_pipex->infile, s_pipex->outfile);
	}
	else
	{
		close(s_pipex->outfile);
		close(s_pipex->pipe1[0]);
		close(s_pipex->pipe2[0]);
		close(s_pipex->pipe2[1]);
		if (s_pipex->infile < 0)
			infile_error(s_pipex);
		if (s_pipex->here_doc == 1)
			here_doc(s_pipex);
		redirect(s_pipex->infile, s_pipex->pipe1[1]);
	}
}

static void	child_last(t_pipex *s_pipex, int child_nr)
{
	close(s_pipex->infile);
	if (child_nr % 2 == 0)
	{
		close(s_pipex->pipe1[1]);
		close(s_pipex->pipe2[0]);
		close(s_pipex->pipe2[1]);
		redirect(s_pipex->pipe1[0], s_pipex->outfile);
	}
	else
	{
		close(s_pipex->pipe2[1]);
		close(s_pipex->pipe1[0]);
		close(s_pipex->pipe1[1]);
		redirect(s_pipex->pipe2[0], s_pipex->outfile);
	}
}

static void	child_process(t_pipex *s_pipex, char *envp[], int child_nr)
{
	char	*path;
	t_cmd	*right_cmd_node;

	if (child_nr == 1)
		child_first(s_pipex);
	else if (child_nr == s_pipex->forks)
		child_last(s_pipex, child_nr);
	else
		child_middle(s_pipex, child_nr);
	right_cmd_node = get_node(s_pipex->s_cmd_lst, child_nr);
	path = get_right_path(right_cmd_node->cmd, s_pipex->envp_pths);
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

	if (make_pipes(s_pipex->pipe1, s_pipex->pipe2) != 0)
	{
		perror("pipex: pipe error");
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
