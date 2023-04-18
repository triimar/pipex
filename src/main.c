/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:39:27 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/18 23:21:39 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	open_files(t_pipex *s_pipex, char *infile, char *outfile)
{
	s_pipex->infile = open(infile, O_RDONLY);
	if (s_pipex->infile < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(infile);
	}
	s_pipex->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (s_pipex->outfile < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(outfile);
		exit (EXIT_FAILURE);
	}
}

static int	ft_get_cmd(t_cmd *s_cmd, char *argv)
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

static int	pipex_init(t_pipex *s_pipex, char **argv, char **envp)
{
	int	i;
	int	arg_nr;

	i = 0;
	arg_nr = 1;
	s_pipex->envp_pths = NULL;
	if (all_paths(s_pipex, envp) != 0)
		return (1);
	while (++arg_nr <= 3)
	{
		if (ft_get_cmd(&s_pipex->exec[i], argv[arg_nr]) != 0)
			return (1);
		s_pipex->exec[i].args = ft_split(argv[arg_nr], ' ');
		if (!s_pipex->exec[i].args)
			return (1);
		i++;
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
