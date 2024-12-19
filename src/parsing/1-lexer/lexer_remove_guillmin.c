/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_remove_guillmin.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viavon <viavon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:20:49 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 19:41:46 by viavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_quote(char ch)
{
	return (ch == '\'' || ch == '"');
}

static void	copy_without_quotes(const char *str, char *result, char quote_char)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && (quote_char == '\0' || str[i] == quote_char))
		{
			if (quote_char == '\0')
				quote_char = str[i];
			else
				quote_char = '\0';
		}
		else
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
}

char	*remove_first_quote_pair(const char *str)
{
	char	*result;
	char	*dup_result;

	result = safe_malloc(ft_strlen(str) + 1);
	copy_without_quotes(str, result, '\0');
	dup_result = ft_strdup(result);
	if (!dup_result)
	{
		printf("error allocation\n");
		exit(EXIT_FAILURE);
	}
	free(result);
	return (dup_result);
}
