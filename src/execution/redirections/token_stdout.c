/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_stdout.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 01:10:47 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:12 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	close_evv(t_main *main, int fd)
{
	perror("dup2");
	close(fd);
	close(main->fds->out);
	close(main->fds->in);
}

int	handle_token_stdout(t_lexer *temp, t_main *main)
{
	int	fd;

	if (temp && temp->type == TOKEN_STDOUT)
	{
		temp = temp->next;
		if (temp && temp->type == TOKEN_ARG)
		{
			fd = open(temp->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (return_error_open_fd());
			if (main->fds->changed_stdout == 0)
			{
				main->fds->out = dup(STDOUT);
				main->fds->changed_stdout = 1;
			}
			if (dup2(fd, STDOUT) == -1)
			{
				close_evv(main, fd);
				return (1);
			}
			close(fd);
		}
	}
	return (0);
}
