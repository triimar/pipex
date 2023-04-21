/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:18:50 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/21 18:20:58 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_pipex *s_pipex)
{
	char	*line;
	int		len;

	line = get_next_line(s_pipex->infile);
	if (!line)
	{
		perror("pipex: here_doc");
		close(s_pipex->infile);
		close(s_pipex->pipe1[1]);
		pipex_free(s_pipex);
		exit(EXIT_FAILURE);
	}
	while (line)
	{
		len = ft_strlen(line) - 1;
		if (ft_str_same(line, s_pipex->s_cmd_lst->cmd, len) == 0)
			break ;
		write(s_pipex->pipe1[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(s_pipex->infile);
	}
	close(s_pipex->infile);
	close(s_pipex->pipe1[1]);
	exit(EXIT_SUCCESS);
}
