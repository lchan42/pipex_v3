/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:11:28 by lchan             #+#    #+#             */
/*   Updated: 2021/12/13 23:14:20 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	index;

	index = 0;
	if (!s1 || !s2)
		return (NULL);
	joined = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	while (s1 && *s1 != '\0')
	{
		joined[index] = *s1;
		s1++;
		index++;
	}
	while (s2 && *s2 != '\0')
	{
		joined[index] = *s2;
		s2++;
		index++;
	}
	joined[index] = '\0';
	return (joined);
}
