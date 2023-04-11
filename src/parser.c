/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 19:42:52 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/12 00:13:08 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	get_command(t_cmd *s_cmd, char *input)
{
	int		i;

	i = 0;
	while (*(input + i) != 0 && *(input + i) != ' ')
		i++;
	s_cmd->cmd = malloc((i + 2 * sizeof(char)));
	if (!s_cmd->cmd)
		return(5); //
	s_cmd->cmd[0] = '/';
	ft_strlcpy((s_cmd->cmd + 1), input, (i + 1));
	// printf("Command is: %s", command);
	return (0);
}

char	**pipex_parser(t_cmd *s_cmd, char *input)
{
	get_command(s_cmd, input);
	printf("Command is: %s\n", s_cmd->cmd);
	s_cmd->arguments = ft_split(input, ' ');
	if (!s_cmd->arguments)
		return (0);
	return (s_cmd->arguments);
}
