/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:24:01 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/20 20:28:45 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_str_identical(const char *s1, const char *s2, size_t len_s1)
{
	if (len_s1 == 0)
		return (0);
	if (ft_strlen(s2) != len_s1)
		return (1);
	while (len_s1 > 0 && *s1 == *s2 && *s1 != 0 && *s2 != 0)
	{
		len_s1--;
		s1++;
		s2++;
	}
	if (len_s1 == 0 && *s2 == 0)
		return (0);
	return (1);
}

