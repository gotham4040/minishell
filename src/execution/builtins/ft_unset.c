/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:47:48 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:12 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static size_t	env_size(char *env)
{
	size_t		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	return (i);
}

static void	free_node(t_main *main, t_env *env)
{
	if (main->env == env && env->next == NULL)
	{
		ft_memdel(main->env->value);
		main->env->value = NULL;
		main->env->next = NULL;
		return ;
	}
	ft_memdel(env->value);
	ft_memdel(env);
}

static int	unset_p1(t_lexer *temp, t_main *main, t_env *env)
{
	if (ft_strncmp(temp->value, env->value, env_size(env->value)) == 0)
	{
		if (env->next)
			main->env = env->next;
		else
			main->env = main->env;
		free_node(main, env);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	ft_unset(t_lexer *temp, t_main *main, t_env *env)
{
	t_env	*tmp;

	env = main->env;
	temp = temp->next;
	if (!temp)
		return (EXIT_FAILURE);
	if (unset_p1(temp, main, env) == 0)
		return (EXIT_SUCCESS);
	while (env && env->next)
	{
		if (ft_strncmp(temp->value, env->next->value, \
		env_size(env->next->value)) == 0)
		{
			tmp = env->next->next;
			free_node(main, env->next);
			env->next = tmp;
			dollar_qm(127, 0);
			return (EXIT_SUCCESS);
		}
		env = env->next;
	}
	return (EXIT_SUCCESS);
}
