/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thilefeb <thilefeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:40:42 by thilefeb          #+#    #+#             */
/*   Updated: 2024/12/12 21:54:56 by thilefeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdlib.h>
# include <limits.h>
# include <linux/limits.h>
# include <sys/types.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <errno.h>
# include <sys/stat.h>
# include <string.h>
# include <termios.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define END 7

# define ENV 1
# define SECRET_ENV 2
# define BUFF_SIZE 4096
# define STDIN STDIN_FILENO
# define STDOUT STDOUT_FILENO
# define STDERR STDERR_FILENO
# define SUCCESS 1
# define ERROR 0

extern int	g_child_running;

typedef enum e_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT,
	TOKEN_CMD,
	TOKEN_BUILT_IN,
	TOKEN_STDIN,
	TOKEN_STDOUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ARG,
}	t_type;

typedef struct s_lexer
{
	char			*value;
	t_type			type;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_fd
{
	int	out;
	int	in;
	int	changed_stdout;
	int	changed_stdin;
}	t_fd;

typedef struct s_main
{
	t_env			*env;
	t_fd			*fds;
	struct s_data	*data;
	int				j;
	pid_t			pid;
	int				pipe_count;
}				t_main;

typedef struct s_data
{
	t_lexer	*lexer;
	char	*a_line;
	char	*a_none_lexed;
	char	**a_tab;
	char	**result;
	char	*word;
	int		count;
	int		word_count;
	int		i;
	int		j;
	int		k;
	int		i_2;
	t_env	*env;
}	t_data;

// parsing

char	*ft_strndup(const char *s, size_t n);
int		ft_strtab(char **str);
void	ft_error_lauch(void);
void	ft_error_quotes(void);
void	error_pipe(void);
int		check_quotes(const char *str);
t_lexer	*lexation(struct s_data *data);
int		contient_variable_environnement(const char *chaine);
int		process_character(t_data *data, int *quote_state, \
		char *res, int *res_i);
char	*process_string(struct s_data *data);
char	**split_string(struct s_data *data);
char	*remove_first_quote_pair(const char *str);
t_lexer	*create_lexer_from_strings(struct s_data *data);
int		is_command(const char *cmd);
t_lexer	*find_good_token(t_lexer *head);
void	correct_tokens(t_lexer *head);
int		check_pipe_and_redirection(t_lexer *head);
int		check_after_heredoc(t_lexer *head);
int		check_parsing(t_lexer *head);
int		check_first_arg(t_lexer *head);
void	clean_list(t_lexer *head);
void	clean_string(struct s_data *data);
int		ft_isalnum2(int c);
void	*safe_malloc(size_t size);
int		is_operator_char(char c);
void	exit_printf(void);

// exec

size_t	size_env(t_env *lst);
char	*env_to_str(t_env *lst);
int		env_init(t_main *mini, char **env_array);
int		env_add(const char *value, t_env *env);
char	*get_env_name(char *dest, const char *src);
int		is_in_env(t_env *env, char *args);
int		str_env_len(char **env);
void	sort_env(char **tab, int env_len);
void	print_sorted_env(t_env *env);
int		is_env_char(int c);
int		is_valid_env(char *env);
int		env_value_len(const char *env);
char	*env_value(char *env);
char	*get_env_value(char *arg, t_env *env);
int		ft_echo(t_lexer *temp);
int		ft_pwd(void);
int		ft_cd(t_lexer *temp, t_main *main);
int		ft_env(t_env *env);
void	ft_exit(t_lexer *temp, t_main *main);
int		ft_export(t_lexer *temp, t_main *main);
int		ft_unset(t_lexer *temp, t_main *mini, t_env *env);
int		execution(t_lexer *lexer, t_main *main);
char	*find_cmd_path_if_exist(char *cmd);
void	handle_signal(int sig);
int		update_oldpwd(t_env *env, char *str);
void	free_execution(t_main *main);
void	clean_list(t_lexer *head);
void	free_execution(t_main *main);
void	clean_string(struct s_data *data);
int		update_shlvl(t_env *env);
int		malloc_fds(t_main *main);
int		dollar_qm(int status, int m);
int		exec_builtin_p1(t_lexer *temp, t_main *main);
int		exec_builtin_p2(t_lexer *temp, t_main *main);
int		exec_builtin(t_lexer *temp, t_main *main);
void	handle_bs(int sig);
int		check_if_path_exists(t_env *env);
void	wait_process_no_pipe(pid_t pid);
int		exec_no_pipe_token_cmd(t_lexer *temp, t_main *main);
char	**convert_env_to_array(t_env *env);
size_t	count_args(t_lexer *temp);
size_t	count_pipes(t_lexer *temp);
void	child_process_no_pipe(t_lexer *temp, t_main *main);
char	**convert_env_to_array(t_env *env);
int		**create_inner_pipes(int **pipes, t_main *main, int i);
int		**create_pipes(t_main *main);
t_lexer	*find_command_in_command(t_lexer *temp);
t_lexer	*move_to_next_command(t_lexer *temp);
int		return_error_open_fd(void);
int		handle_token_stdin(t_lexer *temp, t_main *main, int fd);
int		handle_token_stdout(t_lexer *temp, t_main *main);
int		handle_token_heredoc_p2(t_main *main, int *pipefd);
int		handle_token_heredoc(t_lexer *temp, t_main *main);
int		handle_token_append(t_lexer *temp, t_main *main);
int		handle_redirections(t_lexer *temp, t_main *main);
size_t	count_pipes(t_lexer *temp);
size_t	count_args(t_lexer *temp);
int		setup_stdin_pipes(int i, int **pipefds, t_main *main);
int		setup_stdout_pipes(int i, int **pipefds, t_main *main);
int		setup_pipes(int **pipefds, t_main *main);
void	close_pipes(int **pipefds, t_main *main);
void	exec_with_pipes_wait_parent_process(pid_t *pid_array, \
											int **pipefds, t_main *main);
void	ft_free_intab(int **pipesfds, int tab_count);
void	child_process_with_pipes(t_lexer *temp, t_main *main, int **pipefds);
int		execute_with_pipes(t_lexer *head, t_main *main, int **pipefds);
int		start_exec_no_pipes(t_lexer *temp, t_main *main);
void	exec_with_pipes_token_cmd(t_lexer *temp, t_main *main);
int		error_during_fork(pid_t *pid_array);
int		exec_no_pipe(t_lexer *temp, t_main *main);
int		terminate_fds(t_main *main);
int		check_if_path_valid(char *env_path, int option, t_env *env);
char	*get_env_path(t_env *env, const char *var, size_t len);
int		update_pwd(t_env *env);
int		go_to_path(int option, t_env *env);
void	exec_with_pipes_loop(t_lexer *temp, \
								t_main *main, int **pipefds, pid_t *pid_array);
int		error_during_fork(pid_t *pid_array);
int		is_env_char(int c);
char	*terminate_and_return_old_pwd(char *oldpwd, int j);
int		export_print_error(int error, const char *arg);

#endif
