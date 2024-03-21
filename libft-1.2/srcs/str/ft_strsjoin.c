/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcros <gcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:10:08 by gcros             #+#    #+#             */
/*   Updated: 2023/12/18 12:37:10 by gcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "str.h"

char	*ft_strsjoin(char **strs, char sep)
{
	char	*str;
	char	*p;
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (strs[i])
		count += ft_strlen(strs[i++]);
	if (count + i == 0)
		return (NULL);
	str = malloc(count + i);
	if (!str)
		return (NULL);
	i = 0;
	p = str;
	while (strs[i])
	{
		p = ft_stpcpy(p, strs[i++]);
		*(p++) = sep;
	}
	*(p - 1) = '\0';
	return (str);
}
