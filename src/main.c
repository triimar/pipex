/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:39:27 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/15 14:50:15 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_files(t_pipex *s_pipex, char *infile, char *outfile)
{
	s_pipex->infile = open(infile, O_RDONLY);
	if (s_pipex->infile < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(infile, 2);
		perror(":");
		s_pipex->infile = 0;
	}
	s_pipex->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (s_pipex->outfile < 0)
	{
		ft_putstr_fd("pipex: ", 2);
		ft_putstr_fd(outfile, 2);
		perror(":");
		exit (EXIT_FAILURE);
	}
}

static int	pipex_init(t_pipex *s_pipex, char **argv, char **envp)
{
	s_pipex->envp_paths = all_paths(envp);
	// if (!s_pipex->envp_paths)
		// return (1);
	s_pipex->exec[0].arguments = ft_split(argv[2], ' ');
	if (!s_pipex->exec[0].arguments)
	{
		if (s_pipex->envp_paths)
			free(s_pipex->envp_paths);
		return (1);
	}
	s_pipex->exec[1].arguments = ft_split(argv[3], ' ');
	if (!s_pipex->exec[1].arguments)
	{
		if (s_pipex->envp_paths)
			free(s_pipex->envp_paths);
		free(s_pipex->exec->arguments[0]);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;

	if (argc != 5)
	{
		ft_putendl_fd("pipex: incorrect number of arguments", 2);
		exit(EXIT_FAILURE);
	}
	open_files(&s_pipex, argv[1], argv[argc - 1]);
	// pipex_parser(&s_pipex.exec[0], argv[2], s_pipex.envp_paths);
	// pipex_parser(&s_pipex.exec[1], argv[3], s_pipex.envp_paths);
	// cmd_parser(&s_pipex.exec[0], argv[2], s_pipex.envp_paths);
	// cmd_parser(&s_pipex.exec[1], argv[3], s_pipex.envp_paths);
	if (pipex_init(&s_pipex, argv, envp) < 0)
	{
		perror("pipex: failure initiating data");
		exit (EXIT_FAILURE);
	}
	pipex(&s_pipex, envp);
	pipex_free(&s_pipex);
// system("leaks pipex");
	return (0);
}

