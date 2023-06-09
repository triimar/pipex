/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarts <tmarts@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 20:24:01 by tmarts            #+#    #+#             */
/*   Updated: 2023/04/21 18:21:28 by tmarts           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_pathjoin(char const *s1, char const *s2)
{
	char	*string;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	string = malloc(s1_len + s2_len + 2);
	if (!string)
		return (NULL);
	while (s1 && *s1 != 0)
		*string++ = *s1++;
	*string = '/';
	string++;
	while (*s2 != 0)
		*string++ = *s2++;
	*string = '\0';
	return (string - s1_len - s2_len - 1);
}

int	ft_str_same(const char *s1, const char *s2, size_t len_s1)
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
