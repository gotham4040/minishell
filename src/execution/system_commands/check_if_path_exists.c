/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_path_exists.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:28:28 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 00:30:32 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_if_path_exists(t_env *env)
{
	int		i;
	char	**tab;
	char	**tab_lign;
	char	*str_env;

	str_env = env_to_str(env);
	tab = ft_split(str_env, '\n');
	ft_memdel(str_env);
	i = 0;
	while (tab[i])
	{
		tab_lign = ft_split(tab[i], '=');
		if (ft_strcmp("PATH", tab_lign[0]) == 0)
		{
			ft_freetab(tab_lign);
			ft_freetab(tab);
			return (1);
		}
		ft_freetab(tab_lign);
		i++;
	}
	ft_freetab(tab);
	return (0);
}
