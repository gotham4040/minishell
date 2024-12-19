/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:20:44 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 21:32:59 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check_quotes_for_lexer(const char *str)
{
	char	open_quote;
	int		i;

	i = 0;
	open_quote = '\0';
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			if (open_quote == '\0')
				open_quote = str[i];
			else if (str[i] == open_quote)
				open_quote = '\0';
		}
		i++;
	}
	if (open_quote != '\0')
		return (ERROR);
	return (SUCCESS);
}

static t_lexer	*create_lexer_node(char *value, t_type type)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	if (check_quotes_for_lexer(value) == SUCCESS)
		node->value = remove_first_quote_pair(value);
	else
		node->value = ft_strdup(value);
	node->type = type;
	node->next = NULL;
	return (node);
}

static t_type	determine_token_type(const char *value)
{
	if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(value, ">") == 0 || ft_strcmp(value, "<") == 0 \
	|| ft_strcmp(value, "<<") == 0 || ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIRECT);
	else
		return (TOKEN_WORD);
}

static void	add_lexer_node(t_lexer **head, char *value)
{
	t_type	type;
	t_lexer	*new_node;
	t_lexer	*temp;

	type = determine_token_type(value);
	new_node = create_lexer_node(value, type);
	if (*head == NULL)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_node;
	}
}

t_lexer	*create_lexer_from_strings(t_data *data)
{
	t_lexer	*head;
	int		i;

	head = NULL;
	i = 0;
	while (i < data->count)
	{
		add_lexer_node(&head, data->a_tab[i]);
		i++;
	}
	return (head);
}
