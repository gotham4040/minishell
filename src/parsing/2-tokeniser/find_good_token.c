/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_good_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:20:20 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 21:31:59 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_built_in(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "cd") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "pwd") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "export") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "unset") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "env") == 0)
		return (SUCCESS);
	else if (ft_strcmp(str, "exit") == 0)
		return (SUCCESS);
	else
		return (ERROR);
}

static int	is_command_path(char *path)
{
	struct stat	path_stat;

	if (!path || ft_strlen(path) == 0)
		return (ERROR);
	if (access(path, X_OK) == 0)
	{
		if (stat(path, &path_stat) == 0)
		{
			if (S_ISREG(path_stat.st_mode))
				return (SUCCESS);
		}
	}
	return (ERROR);
}

static t_type	find_token(char *value, t_type token)
{
	t_type	token_temp;

	if (token == TOKEN_WORD && is_built_in(value) == SUCCESS)
		token_temp = TOKEN_BUILT_IN;
	else if (token == TOKEN_WORD && is_command(value) == SUCCESS && \
	is_built_in(value) == ERROR)
		token_temp = TOKEN_CMD;
	else if (token == TOKEN_WORD && is_command_path(value) == SUCCESS)
		token_temp = TOKEN_CMD;
	else if (token == TOKEN_REDIRECT)
	{
		if (ft_strcmp(value, ">") == 0)
			token_temp = TOKEN_STDOUT;
		else if (ft_strcmp(value, "<") == 0)
			token_temp = TOKEN_STDIN;
		else if (ft_strcmp(value, ">>") == 0)
			token_temp = TOKEN_APPEND;
		else if (ft_strcmp(value, "<<") == 0)
			token_temp = TOKEN_HEREDOC;
	}
	else if (token != TOKEN_PIPE && token == TOKEN_WORD)
		token_temp = TOKEN_ARG;
	else
		token_temp = TOKEN_PIPE;
	return (token_temp);
}

t_lexer	*find_good_token(t_lexer *head)
{
	t_lexer	*current;

	current = head;
	while (current != NULL)
	{
		current->type = find_token(current->value, current->type);
		current = current->next;
	}
	return (head);
}
