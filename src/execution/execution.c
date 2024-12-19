/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:25:44 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:54:04 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	terminate_fds(t_main *main)
{
	if (main->fds->changed_stdin)
	{
		if (dup2(main->fds->in, STDIN) == -1)
		{
			perror("dup2");
			return (1);
		}
		main->fds->changed_stdin = 0;
	}
	if (main->fds->changed_stdout)
	{
		if (dup2(main->fds->out, STDOUT) == -1)
		{
			perror("dup2");
			return (1);
		}
		main->fds->changed_stdout = 0;
	}
	return (0);
}

int	exec_no_pipe(t_lexer *temp, t_main *main)
{
	pid_t	pid;

	(void)pid;
	while (temp)
	{
		if (temp->type == TOKEN_BUILT_IN)
		{
			if (exec_builtin(temp, main) == -1)
			{
				perror("execution of builtin failed");
				return (0);
			}
		}
		else if (temp->type == TOKEN_CMD)
		{
			if (exec_no_pipe_token_cmd(temp, main) != 0)
				return (1);
		}
		temp = temp->next;
	}
	g_child_running = 0;
	return (0);
}

static void	check_path(char *path)
{
	if (!path)
	{
		perror("command not found");
		exit(1);
	}
}

void	exec_with_pipes_token_cmd(t_lexer *temp, t_main *main)
{
	char	*path;
	char	**array;
	size_t	f;
	size_t	number_of_args;
	char	**args;

	path = find_cmd_path_if_exist(temp->value);
	check_path(path);
	number_of_args = count_args(temp->next);
	args = malloc((number_of_args + 2) * sizeof(char *));
	if (!args)
		exit(0);
	f = 0;
	while (temp && f < number_of_args + 1)
	{
		args[f] = temp->value;
		temp = temp->next;
		f++;
	}
	args[f] = NULL;
	array = convert_env_to_array(main->env);
	execve(path, args, array);
	perror("execve failed");
	exit(1);
}

int	execution(t_lexer *head, t_main *main)
{
	t_lexer	*temp;
	int		**pipefds;
	int		result;

	temp = head;
	main->pipe_count = count_pipes(temp);
	main->fds->changed_stdin = 0;
	main->fds->changed_stdout = 0;
	if (main->pipe_count == 0)
	{
		start_exec_no_pipes(temp, main);
	}
	temp = head;
	if (main->pipe_count > 0)
	{
		pipefds = create_pipes(main);
		if (!pipefds)
			return (1);
		result = execute_with_pipes(temp, main, pipefds);
		if (result != 0)
			return (1);
	}
	temp = head;
	return (0);
}
