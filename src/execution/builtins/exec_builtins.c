/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:17:11 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:12 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exec_builtin_p1(t_lexer *temp, t_main *main)
{
	if (ft_strcmp(temp->value, "cd") == 0)
	{
		return (ft_cd(temp, main));
	}
	if (ft_strcmp(temp->value, "echo") == 0)
	{
		dollar_qm(ft_echo(temp), 0);
	}
	if (ft_strcmp(temp->value, "env") == 0)
	{
		return (dollar_qm(ft_env(main->env), 0));
	}
	if (ft_strcmp(temp->value, "exit") == 0)
	{
		ft_exit(temp, main);
	}
	return (0);
}

int	exec_builtin_p2(t_lexer *temp, t_main *main)
{
	if (ft_strcmp(temp->value, "export") == 0)
	{
		return (ft_export(temp, main));
	}
	if (ft_strcmp(temp->value, "pwd") == 0)
	{
		return (ft_pwd());
	}
	if (ft_strcmp(temp->value, "unset") == 0)
	{
		return (ft_unset(temp, main, NULL));
	}
	return (0);
}

int	exec_builtin(t_lexer *temp, t_main *main)
{
	int	result;

	result = exec_builtin_p1(temp, main);
	result = exec_builtin_p2(temp, main);
	return (result);
}
