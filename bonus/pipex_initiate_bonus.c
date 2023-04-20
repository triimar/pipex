/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_initiate_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 23:25:57 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/20 20:34:08 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"


void	open_files(t_pipex *s_pipex, char *infile, char *outfile)
{
	if (ft_str_identical(infile, "here_doc", ft_strlen(infile)) == 0)
	{
		s_pipex->here_doc = 1;
		s_pipex->infile = STDIN_FILENO;
		s_pipex->outfile = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	}
	else
	{
		s_pipex->infile = open(infile, O_RDONLY);
		if (s_pipex->infile < 0)
		{
			ft_putstr_fd("pipex: ", STDERR_FILENO);
			perror(infile);
		}
		s_pipex->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	if (s_pipex->outfile < 0)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		perror(outfile);
		exit (EXIT_FAILURE);
	}
}

static void	ft_lstadd_back_pipex(t_cmd **lst, t_cmd *new)
{
	t_cmd	*last;

	if (*lst == 0)
	{
		*lst = new;
		return ;
	}		
	last = *lst;
	while (last->next != NULL)
		last = last->next;
	last->next = new;
	return ;
}

int	pipex_init(t_pipex *s_pipex, char **argv, char **envp)
{
	int		arg_nr;
	t_cmd	*new_node;

	arg_nr = 1;
	s_pipex->envp_pths = NULL;
	if (all_paths(s_pipex, envp) != 0)
		return (1);
	s_pipex->pids = (int *)malloc((s_pipex->forks) * sizeof(int));
	if (!s_pipex->pids)
		return (1);
	s_pipex->s_cmd_lst = NULL;
	while (++arg_nr <= s_pipex->forks + 1)
	{
		new_node = (t_cmd *)malloc(sizeof(t_cmd));
		if (!new_node)
			return (1);
		new_node->next = NULL;
		if (ft_get_cmd(new_node, argv[arg_nr]) != 0)
			return (1);
		new_node->args = ft_split(argv[arg_nr], ' ');
		if (!new_node->args)
			return (1);
		ft_lstadd_back_pipex(&s_pipex->s_cmd_lst, new_node);
	}
	return (0);
}
