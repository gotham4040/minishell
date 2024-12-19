/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:46:37 by macrespo          #+#    #+#             */
/*   Updated: 2024/12/12 21:53:49 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	print_error(int i)
{
	ft_putstr_fd("cd: ", 2);
	if (i == 1)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (i == 2)
		ft_putstr_fd("Not a directory\n", 2);
	else if (i == 3)
		ft_putstr_fd("chdir\n", 2);
	else if (i == 4)
	{
		ft_putstr_fd("error: getcwd failed\n", 2);
		ft_putstr_fd(strerror(errno), 2);
	}
}

int	update_oldpwd(t_env *env, char *str)
{
	char	*oldpwd;

	if (str == NULL)
	{
		printf("\n1\n");
		return (EXIT_FAILURE);
	}
	oldpwd = ft_strjoin("OLDPWD=", str);
	if (!oldpwd)
	{
		return (EXIT_FAILURE);
	}
	if (is_in_env(env, oldpwd) == 0)
	{
		env_add(oldpwd, env);
	}
	ft_memdel(oldpwd);
	return (EXIT_SUCCESS);
}

int	check_security_and_chdir(t_lexer *temp, t_main *main, int *cd_ret)
{
	struct stat	statbuf;
	char		cwd[PATH_MAX];

	if (stat(temp->value, &statbuf) == -1 || !S_ISDIR(statbuf.st_mode))
	{
		print_error(2);
		return (-1);
	}
	*cd_ret = chdir(temp->value);
	if (*cd_ret == -1)
	{
		print_error(3);
		return (-1);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		print_error(4);
		return (-1);
	}
	update_pwd(main->env);
	update_oldpwd(main->env, cwd);
	return (0);
}

int	ft_cd(t_lexer *temp, t_main *main)
{
	int		cd_ret;

	cd_ret = 0;
	temp = temp->next;
	if (temp == NULL || temp->type == TOKEN_STDOUT || \
	temp->type == TOKEN_APPEND)
		return (go_to_path(0, main->env));
	else if (temp->type == TOKEN_ARG && ft_strcmp(temp->value, "-") == 0)
		cd_ret = go_to_path(1, main->env);
	else if (temp->type)
	{
		if (access(temp->value, F_OK) == -1)
		{
			print_error(1);
			return (dollar_qm(1, 0));
		}
		if (check_security_and_chdir(temp, main, &cd_ret) == -1)
		{
			return (dollar_qm(1, 0));
		}
	}
	return (cd_ret);
}
