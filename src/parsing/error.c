/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viavon <viavon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 00:20:58 by viavon            #+#    #+#             */
/*   Updated: 2024/12/12 19:48:49 by viavon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_error_lauch(void)
{
	printf("erreur argument de lancement");
	exit(EXIT_FAILURE);
}

void	ft_error_quotes(void)
{
	printf("Error: found not closed quote\n");
}

void	error_pipe(void)
{
	printf("Error pipe\n");
}

void	exit_printf(void)
{
	printf("Memory allocation failed\n");
	exit(EXIT_FAILURE);
}
