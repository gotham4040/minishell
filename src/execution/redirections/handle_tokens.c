/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 01:23:08 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:12 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_redirections(t_lexer *temp, t_main *main)
{
	while (temp && temp->type != TOKEN_PIPE)
	{
		handle_token_stdin(temp, main, 0);
		handle_token_heredoc(temp, main);
		handle_token_stdout(temp, main);
		handle_token_append(temp, main);
		if (temp)
			temp = temp->next;
	}
	return (0);
}
