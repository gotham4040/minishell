/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_no_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:37:21 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:12 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_no_pipe_token_cmd(t_lexer *temp, t_main *main)
{
	int		path_exists;
	pid_t	pid;

	path_exists = check_if_path_exists(main->env);
	if (path_exists == 0)
	{
		perror(temp->value);
		return (1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		dollar_qm(1, 0);
		return (1);
	}
	else if (pid == 0)
		child_process_no_pipe(temp, main);
	else
		wait_process_no_pipe(pid);
	return (0);
}
