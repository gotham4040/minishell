/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:56:18 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:47:12 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	dash_n(char *value)
{
	size_t	i;

	if (value[0] == '-' && value[1] == 'n')
	{
		i = 2;
		while (value[i])
		{
			if (value[i] != 'n')
			{
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	echo_nothing(void)
{
	write(1, "\n", 1);
	return (0);
}

int	ft_echo(t_lexer *temp)
{
	int	n_option;

	temp = temp->next;
	if (!temp)
		return (echo_nothing());
	n_option = dash_n(temp->value);
	if (n_option)
		temp = temp->next;
	while (temp && dash_n(temp->value))
		temp = temp->next;
	while (temp && temp->type != TOKEN_PIPE && \
	temp->type != TOKEN_STDOUT && temp->type != TOKEN_APPEND)
	{
		if (temp->type == TOKEN_ARG)
		{
			ft_putstr_fd(temp->value, 1);
			if (temp->next && temp->next->type == TOKEN_ARG)
				write(1, " ", 1);
		}
		temp = temp->next;
	}
	if (n_option == 0)
		write(1, "\n", 1);
	return (0);
}
