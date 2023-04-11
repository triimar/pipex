/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:39:27 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/12 00:15:13 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;

	if (argc < 4)
		ft_printf("not enough arguments");
	s_pipex.infile = open(argv[1], O_RDONLY);
	if (s_pipex.infile < 0)
		perror("file error");
	s_pipex.outfile = open(argv[argc - 1], O_WRONLY);
	if (s_pipex.outfile < 0)
		perror("file error");
	s_pipex.n_forks = argc - 3;
	s_pipex.paths = all_paths(envp);
	pipex_parser(&s_pipex.exec[0], argv[2]);
	pipex_parser(&s_pipex.exec[1], argv[3]);
	pipex(&s_pipex);
	// system("leaks pipex");
	ft_free_split(s_pipex.paths);
	ft_free_split(s_pipex.exec[0].arguments);
	free(s_pipex.exec[0].cmd);
	free(s_pipex.exec[1].cmd);
	ft_free_split(s_pipex.exec[1].arguments);
	return (0);
}
