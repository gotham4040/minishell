/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viavon <viavon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:18:25 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 19:22:03 by viavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_freetab(char **tabstr)
{
	int	i;

	i = 0;
	while (tabstr[i])
	{
		free(tabstr[i]);
		i++;
	}
	free(tabstr);
	return (NULL);
}
