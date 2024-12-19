/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_var_env_guillemin.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:20:09 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 23:02:17 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	contient_variable_environnement(const char *chaine)
{
	while (*chaine)
	{
		if (*chaine == '$')
		{
			chaine++;
			if (isalpha(*chaine) || *chaine == '_' || *chaine == '?')
			{
				chaine++;
				while (isalnum(*chaine) || *chaine == '_' || *chaine == '?')
					chaine++;
				return (SUCCESS);
			}
		}
		chaine++;
	}
	return (ERROR);
}

static char	*ft_getenv(t_data *data, const char *var_name)
{
	struct s_env	*temp;
	size_t			var_len;

	temp = data->env;
	if (!temp || !var_name)
		return (NULL);
	var_len = ft_strlen(var_name);
	while (temp)
	{
		if (ft_strncmp(temp->value, var_name, var_len) == 0 && \
	temp->value[var_len] == '=')
			return (ft_strdup(&temp->value[var_len + 1]));
		temp = temp->next;
	}
	return (NULL);
}

static char	*replace_env_variable(t_data *data, const char *str, int *index)
{
	int		start;
	char	*env_name;
	char	*env_value;

	start = *index + 1;
	(*index)++;
	while (ft_isalnum(str[*index]) || str[*index] == '_' || str[*index] == '?')
	{
		if (str[*index] == '?')
		{
			(*index)++;
			return (ft_itoa(dollar_qm(-1, 1)));
		}
		(*index)++;
	}
	env_name = ft_strndup(&str[start], *index - start);
	if (!env_name)
		exit_printf();
	env_value = ft_getenv(data, env_name);
	free(env_name);
	if (env_value)
		return (env_value);
	return (ft_strdup(""));
}

int	process_character(t_data *data, int *quote_state, char *res, int *res_i)
{
	char	*replacement;

	if (data->a_line[data->i_2] == '\'')
		*quote_state ^= 1;
	else if (data->a_line[data->i_2] == '"')
		*quote_state ^= 2;
	else if (data->a_line[data->i_2] == '$' && !(*quote_state & 1))
	{
		if (data->a_line[data->i_2 + 1] == '\0' || \
	!(ft_isalnum2(data->a_line[data->i_2 + 1])))
			res[(*res_i)++] = '$';
		else
		{
			replacement = replace_env_variable(data, data->a_line, &data->i_2);
			ft_strcpy(&res[*res_i], replacement);
			*res_i += ft_strlen(replacement);
			free(replacement);
			return (data->i_2 - 1);
		}
	}
	else
		res[(*res_i)++] = data->a_line[data->i_2];
	res[*res_i] = '\0';
	return (data->i_2);
}

char	*process_string(t_data *data) //ajouter main
{
	char	*result;
	int		result_index;
	int		quote_state;

	data->i_2 = 0;
	result_index = 0;
	quote_state = 0;
	result = safe_malloc(ft_strlen(data->a_line) * 100 + 1);
	while (data->a_line[data->i_2] != '\0')
	{
		data->i_2 = process_character(data, &quote_state, \
	result, &result_index);
		data->i_2++;
	}
	free(data->a_line);
	return (result);
}
