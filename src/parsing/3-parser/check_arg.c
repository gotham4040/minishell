/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:20:30 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 21:31:35 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_type	is_redirection_type(int type)
{
	return (type == TOKEN_STDIN || type == TOKEN_STDOUT || \
	type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

int	check_pipe_and_redirection(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE && current->next == NULL)
			return (ERROR);
		else if (current->type == TOKEN_PIPE && \
		current->next->type == TOKEN_PIPE)
			return (ERROR);
		else if (is_redirection_type(current->type) && current->next == NULL)
			return (ERROR);
		else if (is_redirection_type(current->type) \
		&& current->next->type != TOKEN_ARG)
			return (ERROR);
		current = current->next;
	}
	return (SUCCESS);
}

int	check_after_heredoc(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == TOKEN_HEREDOC && current->next == NULL)
		{
			printf("heredoc need argument\n");
			return (ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	check_first_arg(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	if (current->type != TOKEN_BUILT_IN && current->type != TOKEN_CMD \
	&& !is_redirection_type(current->type))
		return (ERROR);
	while (current != NULL)
	{
		if (current->type == TOKEN_PIPE && current->next != NULL)
		{
			if (current->type == TOKEN_PIPE && (current->next->type \
			!= TOKEN_CMD && current->next->type != TOKEN_BUILT_IN && \
			!is_redirection_type(current->next->type)))
				return (ERROR);
		}
		current = current->next;
	}
	return (SUCCESS);
}

int	check_parsing(t_lexer *head)
{
	if (check_after_heredoc(head) == ERROR || \
	check_pipe_and_redirection(head) == ERROR || check_first_arg(head) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
