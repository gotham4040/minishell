/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_calculus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:46:46 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 00:50:50 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**convert_env_to_array(t_env *env)
{
	size_t	size;
	size_t	i;
	char	**env_array;

	size = ft_lstsize((t_list *)env);
	if (!size)
		return (NULL);
	env_array = safe_malloc((size + 1) * sizeof(char *));
	i = 0;
	while (env)
	{
		env_array[i] = ft_strdup(env->value);
		if (!env_array[i])
		{
			while (i > 0)
				free(env_array[--i]);
			free(env_array);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
