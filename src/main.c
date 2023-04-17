/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:39:27 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/17 22:21:28 by tmarts           ###   ########.fr       */
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

static char	*ft_get_cmd(char *argv)
{
	int		i;
	char	*cmd;

	i = 0;
	while (*(argv + i) != 0 && *(argv + i) == ' ')
		i++;
	// while (ft_isalpha(*(argv + i)) == 1)
	while (*(argv + i + 1) != 0 && *(argv + i + 1) != ' ')
		i++;
	cmd = malloc((i + 2) * sizeof(char));
	if (!cmd)
		return (NULL);
	ft_strlcpy(cmd, argv, (i + 2));
	return (cmd);
}

static int	pipex_init(t_pipex *s_pipex, char **argv, char **envp)
{
	s_pipex->envp_pths = all_paths(envp);
	s_pipex->exec[0].cmd = ft_get_cmd(argv[2]);
	// ft_putstr_fd(s_pipex->exec[0].cmd, 2);
	// ft_putendl_fd("$", 2);
	s_pipex->exec[0].args = ft_split(argv[2], ' ');
	if (!s_pipex->exec[0].args)
	{
		if (s_pipex->envp_pths)
			free(s_pipex->envp_pths);
		return (1);
	}
	s_pipex->exec[1].cmd = ft_get_cmd(argv[3]);
	// ft_putstr_fd(s_pipex->exec[1].cmd, 2);
	// ft_putendl_fd("$", 2);
	s_pipex->exec[1].args = ft_split(argv[3], ' ');
	if (!s_pipex->exec[1].args)
	{
		if (s_pipex->envp_pths)
			free(s_pipex->envp_pths);
		free(s_pipex->exec->args[0]);
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
	// ft_putstr_fd(argv[2], 2);
	// ft_putendl_fd("$", 2);
	// ft_putstr_fd(argv[3], 2);
	// ft_putendl_fd("$", 2);
	open_files(&s_pipex, argv[1], argv[argc - 1]);
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
