/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:01:25 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 19:01:29 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_env(t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strchr(temp->value, '='))
			ft_putendl(temp->value);
		temp = temp->next;
	}
	return (1);
}
