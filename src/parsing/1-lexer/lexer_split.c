/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:20:53 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 20:58:55 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	add_word_to_result(t_data *data)
{
	data->word[data->j] = '\0';
	data->result[data->k] = ft_strdup(data->word);
	if (!data->result[data->k])
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(data->word, data->j);
	data->k++;
	data->j = 0;
}

static void	handle_operator(const char *str, t_data *data)
{
	data->word[data->j++] = str[data->i++];
	if (is_operator_char(str[data->i]))
		data->word[data->j++] = str[data->i++];
	add_word_to_result(data);
}

static void	handle_quotes(const char *str, t_data *data)
{
	char	quote_char;

	quote_char = str[data->i++];
	data->word[data->j++] = quote_char;
	while (str[data->i] != quote_char && str[data->i] != '\0')
	{
		data->word[data->j++] = str[data->i++];
	}
	if (str[data->i] == quote_char)
	{
		data->word[data->j++] = str[data->i++];
	}
}

static void	process_word(const char *str, t_data *data)
{
	if (ft_isspace(str[data->i]))
	{
		if (data->j > 0)
			add_word_to_result(data);
		data->i++;
	}
	else if (str[data->i] == '\'' || str[data->i] == '"')
	{
		handle_quotes(str, data);
	}
	else if (is_operator_char(str[data->i]))
	{
		if (data->j > 0)
			add_word_to_result(data);
		handle_operator(str, data);
	}
	else
	{
		data->word[data->j++] = str[data->i++];
	}
}

char	**split_string(t_data *data)
{
	data->i = 0;
	data->j = 0;
	data->k = 0;
	data->word = safe_malloc((ft_strlen(data->a_none_lexed) + 1) * \
sizeof(data->word));
	data->result = safe_malloc((ft_strlen(data->a_none_lexed) + 1) \
	* sizeof(data->result));
	while (data->a_none_lexed[data->i] != '\0')
	{
		process_word(data->a_none_lexed, data);
	}
	if (data->j > 0)
		add_word_to_result(data);
	data->result[data->k] = NULL;
	data->count = data->k;
	free(data->word);
	data->word = NULL;
	return (data->result);
}
