/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:40:52 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/17 18:21:47 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_free_split(char **p_p)
{
	int	i;

	i = 0;
	if (!p_p)
		return (NULL);
	while (p_p[i])
	{
		free(p_p[i]);
		i++;
	}
	free (p_p);
	return (NULL);
}

void	pipex_free(t_pipex *s_pipex)
{
	ft_free_split(s_pipex->envp_pths);
	ft_free_split(s_pipex->exec[0].args);
	ft_free_split(s_pipex->exec[1].args);
	return ;
}

char	*ft_relative_path(char const *command)
{
	char	*string;
	int		cmd_len;

	cmd_len = ft_strlen(command);
	string = malloc(cmd_len + 3);
	if (!string)
		return (NULL);
	*string = '.';
	string++;
	*string = '/';
	string++;
	while (*command != 0)
		*string++ = *command++;
	*string = '\0';
	return (string - cmd_len - 2);
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
