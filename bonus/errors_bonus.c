/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 23:17:35 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/23 16:10:25 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	path_error(t_pipex *s_pipex, int exit_code, char *command)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(command, STDERR_FILENO);
	if (exit_code == 127)
		ft_putendl_fd(": command not found", STDERR_FILENO);
	if (exit_code == 126)
		ft_putendl_fd(": command not executable", STDERR_FILENO);
	exit(exit_code);
	pipex_free(s_pipex);
}

void	execve_error(t_pipex *s_pipex)
{
	ft_putendl_fd("pipex: execve error: ", STDERR_FILENO);
	pipex_free(s_pipex);
	exit(EXIT_FAILURE);
}

int	fork_pipe_error(int return_val)
{
	if (return_val == 2)
		perror("pipex: pipe error");
	if (return_val == 3)
		perror("pipex: fork error");
	return (return_val);
}
