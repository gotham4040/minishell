/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:47:27 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 19:02:52 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	str_env_len(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_env(char **tab, int env_len)
{
	char	*tmp;
	int		ordered;
	int		i;

	while (1)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		if (ordered)
			break ;
		env_len--;
	}
}

void	custom_putstr(char *str)
{
	int	i;
	int	equal;
	int	end;

	i = 0;
	equal = 0;
	end = 0;
	while (str[i])
	{
		if (str[i] == '=' && equal == 0)
		{
			ft_putchar('=');
			ft_putchar('"');
			equal = 1;
			end = 1;
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	if (end)
		ft_putchar('"');
}

void	print_sorted_env(t_env *env)
{
	int		i;
	char	**tab;
	char	*str_env;

	str_env = env_to_str(env);
	tab = ft_split(str_env, '\n');
	ft_memdel(str_env);
	sort_env(tab, str_env_len(tab));
	i = 0;
	while (tab[i])
	{
		ft_putstr("declare -x ");
		custom_putstr(tab[i]);
		ft_putchar('\n');
		i++;
	}
	ft_freetab(tab);
}
