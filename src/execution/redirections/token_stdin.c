/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 01:07:38 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:12 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_token_stdin(t_lexer *temp, t_main *main, int fd)
{
	if (temp && temp->type == TOKEN_STDIN)
	{
		temp = temp->next;
		if (temp->type == TOKEN_ARG)
		{
			fd = open(temp->value, O_RDONLY);
			if (fd == -1)
				return (return_error_open_fd());
			if (main->fds->changed_stdin == 0)
			{
				main->fds->in = dup(STDIN);
				main->fds->changed_stdin = 1;
			}
			if (dup2(fd, STDIN) == -1)
			{
				perror("dup2");
				close(fd);
				close(main->fds->out);
				close(main->fds->in);
				return (1);
			}
			close(fd);
		}
	}
	return (0);
}
