/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:42:52 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/15 14:42:54 by tmarts           ###   ########.fr       */
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
char	**all_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	if (!envp || envp[0] == 0)
		return (NULL);
	while (envp[i] != 0 && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split((envp[i] + 5), ':');
	if (!paths)
	{
		perror("pipex: ft_split fail");
		exit (EXIT_FAILURE); //
	}
	return (paths);
}

char	*get_right_path(char *command, char **paths)
{
	int		i;
	char	*test_path;

	i = 0;
	if (*command == '/')
		return (command);
	if (!paths || paths[0] == 0)
	{
		test_path = ft_pathjoin(NULL, command);
		if (!paths)
			return (NULL);
		return (test_path);
	}
	while (paths[i] != NULL)
	{
		test_path = ft_pathjoin(paths[i], command);
		if (!test_path)
			return (NULL);
		if (access(test_path, F_OK) == 0)
			return (test_path);
		free(test_path);
		i++;
	}
	return (NULL);
}

// int	cmd_parser(t_cmd *s_cmd, char *input, char **paths)
// {
// 	// s_cmd->arguments = ft_split(input, ' ');
// 	// if (!s_cmd->arguments)
// 	// 	return (1);
// 	s_cmd->path = get_right_path(s_cmd->arguments[0], paths);
// 	if (!s_cmd->path)
// 	{
// 		ft_putstr_fd("pipex: ", 2);
// 		ft_putstr_fd(s_cmd->arguments[0], 2);
// 		ft_putendl_fd(": command not found", 2);
// 		exit(127);
// 	}
// 	else if (access(s_cmd->path, X_OK) != 0)
// 	{
// 		ft_putstr_fd("pipex: ", 2);
// 		ft_putstr_fd(s_cmd->arguments[0], 2);
// 		ft_putendl_fd(": command not executable", 2);
// 		exit(126);
// 	}
// 	return (0);
// }
