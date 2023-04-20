/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_free_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 23:30:51 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/20 20:20:58 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*ft_free_split(char **p_p)
{
	int	i;

	i = 0;
	if (!p_p)
		return (NULL);
	while (p_p[i])
	{
		free(p_p[i]);
		i++;
	}
	free (p_p);
	return (NULL);
}

static void	free_node(t_cmd *s_cmd)
{
	if (s_cmd->cmd)
		free(s_cmd->cmd);
	if (s_cmd->args)
		ft_free_split(s_cmd->args);
	return ;
}

static void	ft_lstclear_pipex(t_cmd *lst)
{
	t_cmd	*tmp;

	if (lst)
	{
		while (lst)
		{
			tmp = (lst)->next;
			free_node(lst);
			(lst) = tmp;
		}
	}
	return ;
}

void	pipex_free(t_pipex *s_pipex)
{
	if (s_pipex->envp_pths)
		ft_free_split(s_pipex->envp_pths);
	if (s_pipex->pids)
		free(s_pipex->pids);
	if (s_pipex->s_cmd_lst)
		ft_lstclear_pipex(s_pipex->s_cmd_lst);
	return ;
}
