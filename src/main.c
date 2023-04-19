/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:39:27 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/19 23:43:37 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;

	if (argc != 5)
	{
		ft_putendl_fd("pipex: incorrect number of arguments", 2);
		exit(EXIT_FAILURE);
	}
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
	system("leaks pipex");
	pipex_free(&s_pipex);
	return (0);
}
