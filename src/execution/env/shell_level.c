/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:55:46 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 00:01:45 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	update_shlvl(t_env *env)
{
	int		nbr;
	char	*char_value;
	char	*output;

	char_value = get_env_value("SHLVL", env);
	nbr = atoi(char_value);
	nbr++;
	free(char_value);
	char_value = ft_itoa(nbr);
	output = ft_strjoin("SHLVL", "=");
	output = ft_strjoin_f_s1(output, char_value);
	is_in_env(env, output);
	free(output);
	free(char_value);
	return (EXIT_SUCCESS);
}
