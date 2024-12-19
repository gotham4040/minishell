/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 01:12:27 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 22:01:14 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	handle_token_heredoc_p2(t_main *main, int *pipefd)
{
	close(pipefd[1]);
	if (main->fds->changed_stdin == 0)
	{
		main->fds->in = dup(STDIN);
		main->fds->changed_stdin = 1;
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		return (1);
	}
	close(pipefd[0]);
	dollar_qm(1, 0);
	return (0);
}

static void	write_line(int pipefd[2], char *line)
{
	write(pipefd[1], line, strlen(line));
	write(pipefd[1], "\n", 1);
	free(line);
}

int	handle_token_heredoc(t_lexer *temp, t_main *main)
{
	char	*delimiter;
	int		pipefd[2];
	char	*line;

	if (temp && temp->type == TOKEN_HEREDOC)
	{
		if (temp->next != NULL)
			delimiter = temp->next->value;
		else
			return (1);
		if (pipe(pipefd) == -1)
			return (return_error_open_fd());
		while (1)
		{
			line = readline("> ");
			if (!line || ft_strcmp(line, delimiter) == 0)
			{
				free(line);
				break ;
			}
			write_line(pipefd, line);
		}
		return (handle_token_heredoc_p2(main, pipefd));
	}
	return (0);
}
