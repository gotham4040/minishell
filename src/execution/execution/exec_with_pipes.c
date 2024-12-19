/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 01:34:03 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:55:20 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exec_with_pipes_wait_parent_process(pid_t *pid_array, \
int **pipefds, t_main *main)
{
	int	i;
	int	status;

	i = 0;
	close_pipes(pipefds, main);
	while (i < main->pipe_count + 1)
	{
		if (waitpid(pid_array[i], &status, 0) == -1)
			perror("waitpid");
		if (WIFEXITED(status))
			dollar_qm(WEXITSTATUS(status), 0);
		else if (WIFSIGNALED(status))
			dollar_qm(128 + WTERMSIG(status), 0);
		else
			dollar_qm(1, 0);
		i++;
	}
	g_child_running = 0;
	ft_free_intab(pipefds, main->pipe_count);
	free(pid_array);
}

void	child_process_with_pipes(t_lexer *temp, t_main *main, int **pipefds)
{
	signal(SIGQUIT, handle_bs);
	main->fds->changed_stdin = 0;
	main->fds->changed_stdout = 0;
	handle_redirections(temp, main);
	setup_pipes(pipefds, main);
	close_pipes(pipefds, main);
	temp = find_command_in_command(temp);
	if (temp->type == TOKEN_BUILT_IN)
	{
		if (exec_builtin(temp, main) == -1)
		{
			perror("exec_builtin failed");
			exit(1);
		}
	}
	else if (temp->type == TOKEN_CMD)
		exec_with_pipes_token_cmd(temp, main);
	exit(0);
}

void	exec_with_pipes_loop(t_lexer *temp, t_main *main, \
int **pipefds, pid_t *pid_array)
{
	int		path_exists;

	main->j = 0;
	while (temp)
	{
		main->pid = fork();
		if (main->pid == -1)
			return ;
		if (main->pid == 0)
		{
			path_exists = check_if_path_exists(main->env);
			if (path_exists == 0)
			{
				perror(temp->value);
				return ;
			}
			child_process_with_pipes(temp, main, pipefds);
		}
		else
		{
			pid_array[main->j++] = main->pid;
			g_child_running = 1;
		}
		temp = move_to_next_command(temp);
	}
}

int	execute_with_pipes(t_lexer *head, t_main *main, int **pipefds)
{
	t_lexer	*temp;
	pid_t	*pid_array;

	temp = head;
	pid_array = malloc((main->pipe_count + 1) * sizeof(pid_t));
	if (!pid_array)
	{
		perror("malloc failed");
		return (1);
	}
	exec_with_pipes_loop(temp, main, pipefds, pid_array);
	exec_with_pipes_wait_parent_process(pid_array, pipefds, main);
	return (0);
}

int	start_exec_no_pipes(t_lexer *temp, t_main *main)
{
	handle_redirections(temp, main);
	if (exec_no_pipe(temp, main) != 0)
		return (1);
	terminate_fds(main);
	return (0);
}
