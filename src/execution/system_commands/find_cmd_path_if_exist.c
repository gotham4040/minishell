/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd_path_if_exist.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 02:33:28 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 02:33:32 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	**ft_split_path(char *path_env)
{
	char	**paths;

	paths = ft_split(path_env, ':');
	if (!paths)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	return (paths);
}

// Construit le chemin complet pour une commande (répertoire + "/" + commande)
static char	*build_full_cmd_path(const char *path, const char *cmd)
{
	size_t	path_len;
	size_t	cmd_len;
	char	*full_cmd_path;

	cmd_len = ft_strlen(cmd);
	path_len = ft_strlen(path);
	full_cmd_path = malloc(path_len + cmd_len + 2);
	if (!full_cmd_path)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	ft_strcpy(full_cmd_path, path);
	ft_strcat(full_cmd_path, "/");
	ft_strcat(full_cmd_path, cmd);
	return (full_cmd_path);
}

// Vérifie si une commande est exécutable en utilisant le chemin complet
static int	is_executable(const char *full_cmd_path)
{
	return (access(full_cmd_path, X_OK) == 0);
}

// Vérifie si une commande est présente dans le $PATH
char	*find_cmd_path_if_exist(char *cmd)
{
	char	*path_env;
	char	**paths;
	int		i;
	char	*full_cmd_path;

	if (is_executable(cmd))
		return (cmd);
	path_env = getenv("PATH");
	if (!path_env || !cmd || strlen(cmd) == 0)
		return (NULL);
	paths = ft_split_path(path_env);
	i = 0;
	while (paths[i])
	{
		full_cmd_path = build_full_cmd_path(paths[i], cmd);
		if (is_executable(full_cmd_path))
		{
			ft_freetab(paths);
			return (full_cmd_path);
		}
		free(full_cmd_path);
		i++;
	}
	ft_freetab(paths);
	return (NULL);
}
