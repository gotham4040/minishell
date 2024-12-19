/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:54:07 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:12 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (env && env->value == NULL)
	{
		env->value = ft_strdup(value);
		return (EXIT_SUCCESS);
	}
	new = malloc(sizeof(t_env));
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (EXIT_SUCCESS);
}

char	*get_env_name(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			ft_memdel(env->value);
			env->value = ft_strdup(args);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	export_loop(t_lexer *temp, t_main *main, int new_env)
{
	int	error_ret;

	while (temp && temp->type == TOKEN_ARG)
	{
		error_ret = is_valid_env(temp->value);
		if (error_ret == 0)
		{
			export_print_error(error_ret, temp->value);
		}
		else
		{
			new_env = is_in_env(main->env, temp->value);
			if (new_env == 0)
				env_add(temp->value, main->env);
		}
		temp = temp->next;
	}
}

int	ft_export(t_lexer *temp, t_main *main)
{
	int		new_env;

	new_env = 0;
	temp = temp->next;
	if (!temp || temp->type != TOKEN_ARG)
	{
		print_sorted_env(main->env);
		return (EXIT_SUCCESS);
	}
	export_loop(temp, main, new_env);
	return (EXIT_SUCCESS);
}
