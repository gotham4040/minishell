/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_qm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:07:37 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 19:08:07 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	dollar_qm(int status, int m)
{
	static int	value;

	if (m == 1)
		return (value);
	else
	{
		status = (status % 256 + 256) % 256;
		value = status;
		return (value);
	}
}

char	*terminate_and_return_old_pwd(char *oldpwd, int j)
{
	oldpwd[j] = '\0';
	return (oldpwd);
}

int	export_print_error(int error, const char *arg)
{
	int		i;

	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR);
	else if (error == 0 || error == -3)
		ft_putstr_fd("export: not a valid identifier: ", STDERR);
	i = 0;
	while (arg[i] && (arg[i] != '=' || error == -3))
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	write(STDERR, "\n", 1);
	return (EXIT_FAILURE);
}
