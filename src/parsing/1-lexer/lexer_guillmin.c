/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_guillmin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:20:41 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 20:58:55 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	check_quotes(const char *str) // check si un guillmet est ferme
{
	char	open_quote;
	int		i;

	i = 0;
	open_quote = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (open_quote == '\0')
			{
				open_quote = str[i];
			}
			else if (str[i] == open_quote)
			{
				open_quote = '\0';
			}
		}
		i++;
	}
	if (open_quote != '\0')
		return (ERROR);
	return (SUCCESS);
}

t_lexer	*lexation(t_data *data)
{
	data->word_count = 0;
	if (check_quotes(data->a_line) == ERROR)
	{
		ft_error_quotes();
		free(data->a_line);
		return (NULL);
	}
	if (contient_variable_environnement(data->a_line) == SUCCESS)
		data->a_none_lexed = process_string(data);
	else
		data->a_none_lexed = data->a_line;
	data->a_tab = split_string(data);
	data->lexer = create_lexer_from_strings(data);
	return (data->lexer);
}
