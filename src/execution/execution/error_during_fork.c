/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_during_fork.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:34:58 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 18:35:29 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	error_during_fork(pid_t *pid_array)
{
	perror("fork");
	dollar_qm(1, 0);
	free(pid_array);
	return (1);
}
