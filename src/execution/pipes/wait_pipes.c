/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:34:21 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 18:58:00 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	wait_process_no_pipe(pid_t pid)
{
	int	status;

	g_child_running = 1;
	if (pid)
	{
		if (waitpid(pid, &status, 0) == -1)
			perror("waitpid");
		if (WIFEXITED(status))
			dollar_qm(WEXITSTATUS(status), 0);
		else if (WIFSIGNALED(status))
			dollar_qm(128 + WTERMSIG(status), 0);
		else
			dollar_qm(1, 0);
	}
}
