/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_inside_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:56:26 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:54:50 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_lexer	*move_to_next_command(t_lexer *temp)
{
	while (temp)
	{
		if (temp->type == TOKEN_PIPE)
			return (temp->next);
		temp = temp->next;
	}
	return (NULL);
}

t_lexer	*find_command_in_command(t_lexer *temp)
{
	while (temp)
	{
		if (temp->type == TOKEN_CMD || temp->type == TOKEN_BUILT_IN)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

size_t	count_args(t_lexer *temp)
{
	size_t	i;

	i = 0;
	while (temp)
	{
		if (temp->type == TOKEN_ARG)
			i++;
		else
			return (i);
		temp = temp->next;
	}
	return (i);
}
