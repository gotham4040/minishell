/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 19:00:34 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 22:43:37 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_digits_only(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0')
	{
		return (0);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	exit_handler(int nbr)
{
	return (nbr % 256);
}

int	free_for_exit(t_lexer *temp, t_main *main)
{
	int	val;

	val = ft_atoi(temp->value);
	clean_list(main->data->lexer);
	clean_string(main->data);
	free_execution(main);
	return (val);
}

void	exit_str_arg(t_lexer *temp, t_main *main)
{
	int	val;

	if (temp->value[0] == '-' || temp->value[0] == '+')
	{
		if (is_digits_only(temp->value + 1))
		{
			val = free_for_exit(temp, main);
			exit(dollar_qm(val, 0));
		}
	}
	else if (is_digits_only(temp->value) == 1)
	{
		val = free_for_exit(temp, main);
		exit(dollar_qm(exit_handler(val), 0));
	}
	printf("exit\nminishell: %s: numeric argument required\n", temp->value);
	free_for_exit(temp, main);
	exit(dollar_qm(2, 0));
}

void	ft_exit(t_lexer *temp, t_main *main)
{
	(void)main;
	temp = temp->next;
	if (temp)
	{
		if (temp->next)
		{
			exit(dollar_qm(1, 0));
			ft_putstr("exit: too many arguments\n");
		}
		else
			exit_str_arg(temp, main);
	}
	else
	{
		ft_putstr("exit\n");
		clean_list(main->data->lexer);
		clean_string(main->data);
		free_execution(main);
		exit(dollar_qm(0, 0));
	}
}
