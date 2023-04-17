/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:42:52 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/17 23:25:25 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**all_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	if (!envp || envp[0] == 0)
	{
		return (NULL);
	}
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split((envp[i] + 5), ':');
			if (!paths)
				perror("pipex: ft_split fail");
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*get_right_path(char *command, char **paths)
{
	int		i;
	char	*test_path;

	i = 0;
	if (*command == '.' && *(command + 1) == '/')
		paths = NULL;
	if (*command == '/')
		return (command);
	if (!command)
		return (NULL);
	if (!paths || paths[0] == 0)
	{
		test_path = ft_relative_path(command);
		if (!test_path)
			return (NULL);
		if (access(test_path, F_OK) == 0)
			return (test_path);
	}
	while (paths && paths[i] != NULL)
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
