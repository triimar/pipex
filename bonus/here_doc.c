/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:18:50 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/20 20:58:51 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_pipex *s_pipex, int outfile)
{
	char	*line;

	line = get_next_line(s_pipex->infile);
	if (!line)
		perror("WHY? malloc error");
	while (line)
	{
		if (ft_str_identical(line, s_pipex->s_cmd_lst->cmd, ft_strlen(line) - 1) == 0)
			break ;
		write(outfile, line, ft_strlen(line));
		// ft_putstr_fd(line, outfile);
		free(line);
		line = get_next_line(s_pipex->infile);
	}
	close(s_pipex->infile);
	close(outfile);
	exit(EXIT_SUCCESS);
}


			// char *one_line = get_next_line(infile);
			// if (!one_line)
			// 	perror("WHY? malloc error");
			// while (one_line)
			// {
			// 	if (ft_str_identical(one_line, s_pipex->s_cmd_lst->cmd, ft_strlen(one_line) - 1) == 0)
			// 		break;
			// 	ft_putstr_fd(one_line, s_pipex->pipes[0][1]);
			// 	free(one_line);
			// 	one_line = get_next_line(infile);
			// }
			// close(s_pipex->infile);
			// close(s_pipex->pipes[0][1]);
			// exit(EXIT_SUCCESS);