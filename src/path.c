/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:49:03 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/13 23:56:18 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		return (NULL); //
	return (paths);
}

char	*get_right_path(char *command, char **paths)
{
	int		i;
	char	*test_path;

	i = 0;
	if (*command == '/')
		return (command);
	if (!paths)
		return (NULL);
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

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**split;
// 	char	*path;
// 	int		i;

// 	split = all_paths(envp);
// 	i = 0;
// 	while (split[i] != 0)
// 		printf("%s\n", split[i++]);
// 	path = get_right_path("/wc", split);
// 	printf("%s\n", path);
// 	ft_free_split(split);
// 	free(path);
// 	return (0);
// }