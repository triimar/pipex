/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:39:27 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/20 20:15:12 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;

	if (argc < 4)
	{
		ft_putendl_fd("pipex: not enough arguments", 2);
		exit(EXIT_FAILURE);
	}
	s_pipex.forks = argc - 3;
	s_pipex.here_doc = 0;
	open_files(&s_pipex, argv[1], argv[argc - 1]);
	if (pipex_init(&s_pipex, argv, envp) < 0)
	{
		perror("pipex: failure initiating data");
		pipex_free(&s_pipex);
		close(s_pipex.infile);
		close(s_pipex.outfile);
		exit (EXIT_FAILURE);
	}
	if (pipex(&s_pipex, envp) != 0)
	{
		pipex_free(&s_pipex);
		exit (EXIT_FAILURE);
	}
	pipex_free(&s_pipex);
	return (0);
}
