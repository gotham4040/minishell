/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:53:41 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 03:01:30 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	**create_inner_pipes(int **pipes, t_main *main, int i)
{
	while (i < main->pipe_count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
		{
			perror("malloc");
			while (i > 0)
				free(pipes[--i]);
			free(pipes);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (i > 0)
				free(pipes[--i]);
			free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (0);
}

int	**create_pipes(t_main *main)
{
	int	**pipes;

	pipes = malloc(main->pipe_count * sizeof(int *));
	if (!pipes)
	{
		perror("malloc");
		return (NULL);
	}
	create_inner_pipes(pipes, main, 0);
	return (pipes);
}
