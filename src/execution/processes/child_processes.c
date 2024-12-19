/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:32:25 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:12 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	check_path(char *path)
{
	if (!path)
	{
		perror("command not found");
		exit(1);
	}
}

void	child_process_no_pipe(t_lexer *temp, t_main *main)
{
	size_t	number_of_args;
	size_t	i;
	char	*path;
	char	**array;
	char	**args;

	signal(SIGQUIT, handle_bs);
	path = find_cmd_path_if_exist(temp->value);
	check_path(path);
	number_of_args = count_args(temp->next);
	args = malloc((number_of_args + 2) * sizeof(char *));
	if (!args)
		exit(1);
	i = 0;
	while (temp && i < number_of_args + 1)
	{
		args[i] = temp->value;
		temp = temp->next;
		i++;
	}
	args[i] = NULL;
	array = convert_env_to_array(main->env);
	execve(path, args, array);
	perror("execve failed");
	exit(1);
}
