/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:42:52 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/14 00:13:32 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

// int	get_command(t_cmd *s_cmd, char *input)
// {
// 	int		i;

// 	i = 0;
// 	while (*(input + i) != 0 && *(input + i) != ' ')
// 		i++;
// 	s_cmd->cmd = malloc((i + 2 * sizeof(char)));
// 	if (!s_cmd->cmd)
// 		return(5); //
// 	s_cmd->cmd[0] = '/';
// 	ft_strlcpy((s_cmd->cmd + 1), input, (i + 1));
// 	// s_cmd->cmd = malloc((i + 1 * sizeof(char)));
// 	// if (!s_cmd->cmd)
// 	// 	return(5); //
// 	// ft_strlcpy(s_cmd->cmd, input, i);
// 	return (0);
// }

int	cmd_parser(t_cmd *s_cmd, char *input, char **paths)
{
	s_cmd->arguments = ft_split(input, ' ');
	if (!s_cmd->arguments)
		return (1);
	s_cmd->path = get_right_path(s_cmd->arguments[0], paths);
	if (!s_cmd->path)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(s_cmd->arguments[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	else if (access(s_cmd->path, X_OK) != 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(s_cmd->arguments[0], 2);
		ft_putendl_fd(": command not executable", 2);
		exit(126);
	}
	return (0);
}
