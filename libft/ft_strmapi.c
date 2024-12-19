/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 13:36:16 by thilefeb          #+#    #+#             */
/*   Updated: 2023/10/23 14:28:35 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*sptr;
	int		index;

	if (!s || !f)
		return (NULL);
	sptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!(sptr))
		return (NULL);
	index = 0;
	while (s[index])
	{
		sptr[index] = f(index, s[index]);
		++index;
	}
	sptr[index] = '\0';
	return (sptr);
}
