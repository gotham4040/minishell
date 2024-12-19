/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 01:30:20 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 18:40:26 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	setup_stdin_pipes(int i, int **pipefds, t_main *main)
{
	int	input_pipe_fd;

	if (main->fds->changed_stdin == 0)
	{
		if (i > 0)
		{
			input_pipe_fd = pipefds[i - 1][0];
			if (dup2(input_pipe_fd, STDIN_FILENO) == -1)
			{
				perror("dup2 - input pipe");
				exit(EXIT_FAILURE);
			}
			close(input_pipe_fd);
		}
	}
	return (EXIT_SUCCESS);
}

int	setup_stdout_pipes(int i, int **pipefds, t_main *main)
{
	int	output_pipe_fd;

	if (main->fds->changed_stdout == 0)
	{
		if (i < main->pipe_count)
		{
			output_pipe_fd = pipefds[i][1];
			if (dup2(output_pipe_fd, STDOUT_FILENO) == -1)
			{
				perror("dup2 - output pipe");
				exit(EXIT_FAILURE);
			}
			close(output_pipe_fd);
		}
	}
	return (SUCCESS);
}

int	setup_pipes(int **pipefds, t_main *main)
{
	setup_stdin_pipes(main->j, pipefds, main);
	setup_stdout_pipes(main->j, pipefds, main);
	return (0);
}

void	close_pipes(int **pipefds, t_main *main)
{
	int	i;

	i = 0;
	while (i < main->pipe_count)
	{
		close(pipefds[i][0]);
		close(pipefds[i][1]);
		i++;
	}
}
