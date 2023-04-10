/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:40:52 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/10 18:41:53 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_free_split(char **p_p)
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
