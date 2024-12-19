/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 01:59:04 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 18:36:26 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_path_valid(char *env_path, int option, t_env *env)
{
	struct stat	statbuf;

	if (option == 0)
	{
		env_path = get_env_path(env, "HOME", 4);
		if (!env_path)
			ft_putendl_fd("minishell : cd: HOME not set", STDERR);
		if (!env_path)
			return (EXIT_FAILURE);
	}
	else if (option == 1)
	{
		env_path = get_env_path(env, "OLDPWD", 6);
		if (!env_path)
			ft_putendl_fd("minishell : cd: OLDPWD not set", STDERR);
		if (!env_path)
			return (EXIT_FAILURE);
	}
	if (access(env_path, F_OK) == -1)
		return (-1);
	if (stat(env_path, &statbuf) == -1 || !S_ISDIR(statbuf.st_mode))
	{
		return (-1);
	}
	return (0);
}

int	update_pwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (EXIT_FAILURE);
	oldpwd = ft_strjoin("PWD=", cwd);
	if (!oldpwd)
		return (EXIT_FAILURE);
	if (is_in_env(env, oldpwd) == 0)
		env_add(oldpwd, env);
	ft_memdel(oldpwd);
	return (EXIT_SUCCESS);
}

int	go_to_path(int option, t_env *env)
{
	char	*env_path;
	int		output;
	int		ret;
	char	cwd[PATH_MAX];

	env_path = NULL;
	output = check_if_path_valid(env_path, option, env);
	if (output)
		return (output);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_memdel(env_path);
		return (-1);
	}
	ret = chdir(env_path);
	if (ret == -1)
	{
		ft_memdel(env_path);
		return (-1);
	}
	update_pwd(env);
	update_oldpwd(env, cwd);
	ft_memdel(env_path);
	return (ret);
}
