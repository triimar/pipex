/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:40:52 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/20 04:55:49 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	close(s_pipex->pipes[0][0]);
	close(s_pipex->pipes[0][1]);
	close(s_pipex->pipes[1][0]);
	close(s_pipex->pipes[1][1]);
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

char	*ft_pathjoin(char const *s1, char const *s2)
{
	char	*string;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	string = malloc(s1_len + s2_len + 2);
	if (!string)
		return (NULL);
	while (s1 && *s1 != 0)
		*string++ = *s1++;
	*string = '/';
	string++;
	while (*s2 != 0)
		*string++ = *s2++;
	*string = '\0';
	return (string - s1_len - s2_len - 1);
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
