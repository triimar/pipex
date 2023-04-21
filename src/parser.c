/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:42:52 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/21 18:16:11 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	all_paths(t_pipex *s_pipex, char **envp)
{
	int		i;

	i = 0;
	while (envp && envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			s_pipex->envp_pths = ft_split((envp[i] + 5), ':');
			if (!s_pipex->envp_pths)
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_get_cmd(t_cmd *s_cmd, char *argv)
{
	int		i;

	i = 0;
	while (*(argv + i) != 0 && *(argv + i) == ' ')
		i++;
	while (*(argv + i + 1) != 0 && *(argv + i + 1) != ' ')
		i++;
	s_cmd->cmd = malloc((i + 2) * sizeof(char));
	if (!s_cmd->cmd)
		return (1);
	ft_strlcpy(s_cmd->cmd, argv, (i + 2));
	return (0);
}

static char	*no_env_path(char *command)
{
	char	*temp_path;

	temp_path = ft_pathjoin("/bin", command);
	if (!temp_path)
		return (NULL);
	if (access(temp_path, F_OK) == 0)
		return (temp_path);
	free(temp_path);
	temp_path = ft_pathjoin("/usr/bin", command);
	if (!temp_path)
		return (NULL);
	if (access(temp_path, F_OK) == 0)
		return (temp_path);
	free(temp_path);
	return (NULL);
}

static char	*path_find_loop(char *command, char **paths)
{
	int		i;
	char	*temp_path;

	i = -1;
	while (paths && paths[++i] != NULL)
	{
		temp_path = ft_pathjoin(paths[i], command);
		if (!temp_path)
			return (NULL);
		if (access(temp_path, F_OK) == 0)
			return (temp_path);
		free(temp_path);
	}
	return (NULL);
}

char	*get_right_path(char *command, char **paths)
{
	if (!command)
		return (NULL);
	if (access(command, F_OK) == 0 && (command[0] == '.'
			|| command[0] == '/' || ft_strchr(command + 1, '/')))
		return (command);
	if (paths)
		return (path_find_loop(command, paths));
	if (!paths)
		return (no_env_path(command));
	return (NULL);
}
