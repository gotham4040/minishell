/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 19:18:04 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/16 18:37:41 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_child_running = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT && g_child_running == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (g_child_running == 1)
		printf("\n");
}

static int	check_empty_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else
			return (ERROR);
	}
	return (SUCCESS);
}

void	main_loop_content(t_main *main, t_data *data)
{
	data->env = main->env;
	add_history(data->a_line);
	data->lexer = lexation(data);
	if (data->lexer != NULL)
	{
		data->lexer = find_good_token(data->lexer);
		correct_tokens(data->lexer);
		if (check_parsing(data->lexer) == ERROR)
		{
			printf("Error command\n");
			dollar_qm(127, 0);
		}
		else if (execution(data->lexer, main) == 1)
		{
			clean_list(data->lexer);
			clean_string(data);
			free_execution(main);
			exit(1);
		}
		clean_list(data->lexer);
		clean_string(data);
	}
}

void	main_loop(t_main *main, t_data *data)
{
	while (1)
	{
		data->a_line = readline("\033[1;36mMinishell$ \033[0m");
		if (data->a_line == NULL)
		{
			free_execution(main);
			printf("exit\n");
			exit(0);
		}
		if (check_empty_line(data->a_line) == SUCCESS)
			free(data->a_line);
		else
		{
			main_loop_content(main, data);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_main	main;
	t_data	data;
	char	cwd[PATH_MAX];

	(void)argv;
	main.data = &data;
	if (!(*env))
	{
		printf("minishell env.\n");
		return (0);
	}
	if (argc != 1)
		return (1);
	if (getcwd(cwd, PATH_MAX) == NULL)
		return (1);
	if (malloc_fds(&main) == 1)
		return (1);
	dollar_qm(0, 0);
	env_init(&main, env);
	update_oldpwd(main.env, cwd);
	update_shlvl(main.env);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	main_loop(&main, &data);
	return (0);
}
