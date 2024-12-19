/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 23:49:03 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 20:58:55 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clean_list(t_lexer *head)
{
	t_lexer	*temp;
	t_lexer	*next;

	temp = head;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp->value);
		free(temp);
		temp = next;
	}
}

void	free_execution(t_main *main)
{
	t_env	*previous_env;

	previous_env = NULL;
	ft_memdel(main->fds);
	while (main->env)
	{
		ft_memdel(main->env->value);
		if (previous_env)
			ft_memdel(previous_env);
		previous_env = main->env;
		main->env = main->env->next;
	}
	ft_memdel(previous_env);
}

void	clean_string(t_data *data)
{
	free(data->a_none_lexed);
	ft_freetab(data->result);
}

int	malloc_fds(t_main *main)
{
	main->fds = malloc(sizeof(t_fd));
	if (!main->fds)
		return (1);
	return (0);
}

void	ft_free_intab(int **pipesfds, int tab_count)
{
	int	i;

	i = 0;
	while (i < tab_count)
	{
		if (pipesfds[i])
			free(pipesfds[i]);
		i++;
	}
	free(pipesfds);
}
