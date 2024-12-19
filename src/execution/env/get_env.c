/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:43:08 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 18:43:14 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_valid_envp_2(char *arg, int i)
{
	if (arg[i] == '=')
	{
		if (arg[i + 1] == '\"')
		{
			i++;
			while (arg[i] && arg[i] != '\"')
				i++;
			if (arg[i] == '\"')
				return (1);
			return (0);
		}
		return (1);
	}
	return (-1);
}

int	is_valid_env(char *arg)
{
	int	i;
	int	result;

	if (!arg || arg[0] == '=')
		return (0);
	i = 0;
	if (ft_isdigit(arg[i]))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	result = is_valid_envp_2(arg, i);
	if (result == 0 || result == 1)
		return (result);
	return (2);
}

int	env_value_len(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(env) + 1;
	env_value = malloc(sizeof(char) * size_alloc);
	if (!env_value)
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_val;

	env_val = ft_strdup("");
	while (env && env->value)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			ft_memdel(env_val);
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	return (env_val);
}
