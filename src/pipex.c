/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:45:59 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/19 23:32:50 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(t_pipex *s_pipex, char *envp[], int child_nr)
{
	char	*path;
	t_cmd	*right_cmd_node;

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
			child_process(s_pipex, envp, i);
		i++;
	}
	close_all(s_pipex);
	ft_waiting(s_pipex->pids);
	return (0);
}
