/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:20:34 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 20:53:32 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_redirection_type(int type)
{
	return (type == TOKEN_STDIN || type == TOKEN_STDOUT || \
	type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static void	handle_expect_command(t_lexer *current, int *expect_command)
{
	if (current->type == TOKEN_CMD || current->type == TOKEN_BUILT_IN)
	{
		*expect_command = 0;
	}
	else if (current->type == TOKEN_PIPE)
	{
		*expect_command = 1;
	}
	else if (is_redirection_type(current->type))
	{
		if (current->next && (current->next->type == TOKEN_CMD || \
		current->next->type == TOKEN_BUILT_IN))
		{
			current->next->type = TOKEN_ARG;
		}
		*expect_command = 1;
	}
}

static void	handle_not_expect_command(t_lexer *current, int *expect_command)
{
	if (current->type == TOKEN_CMD || current->type == TOKEN_BUILT_IN)
	{
		current->type = TOKEN_ARG;
	}
	else if (is_redirection_type(current->type))
	{
		if (current->next && (current->next->type == TOKEN_CMD || \
		current->next->type == TOKEN_BUILT_IN))
		{
			current->next->type = TOKEN_ARG;
		}
	}
	else if (current->type == TOKEN_PIPE)
	{
		*expect_command = 1;
	}
}

void	correct_tokens(t_lexer *head)
{
	t_lexer	*current;
	int		expect_command;

	current = head;
	expect_command = 1;
	while (current != NULL)
	{
		if (expect_command)
		{
			handle_expect_command(current, &expect_command);
		}
		else
		{
			handle_not_expect_command(current, &expect_command);
		}
		current = current->next;
	}
}
