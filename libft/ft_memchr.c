/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:00:40 by thilefeb          #+#    #+#             */
/*   Updated: 2023/10/24 13:16:59 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_cast = (const unsigned char *)s;
	const unsigned char	c_cast = (const unsigned char)c;
	size_t				i;
	void				*ptr;

	i = 0;
	ptr = NULL;
	while (i < n)
	{
		if (s_cast[i] == c_cast)
		{
			ptr = (void *)(s_cast + i);
			return (ptr);
		}
		i++;
	}
	return (ptr);
}
