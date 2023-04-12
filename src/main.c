/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:39:27 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/12 21:28:35 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;

	if (argc != 5)
	{
		ft_putendl_fd("PIPEX: incorrect number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	s_pipex.infile = open(argv[1], O_RDONLY);
	if (s_pipex.infile < 0)
	{
		perror("file error");
		s_pipex.infile = 0;
	}
	s_pipex.outfile = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (s_pipex.outfile < 0)
	{
		perror("file error");
		return (EXIT_FAILURE);
	}
	s_pipex.envp_paths = all_paths(envp);
	pipex_parser(&s_pipex.exec[0], argv[2]);
	pipex_parser(&s_pipex.exec[1], argv[3]);
	if (pipex(&s_pipex, envp) != 0)
		exit(EXIT_FAILURE);
	pipex_free(&s_pipex);
// system("leaks pipex");
	return (0);
}
