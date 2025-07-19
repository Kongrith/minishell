/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:23:28 by rvesterl          #+#    #+#             */
/*   Updated: 2025/07/16 08:38:31 by kkomasat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"
# include "libft/ft_printf.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

# define SHELL_PROMPT "minishell$ "
# define SHELL_ERROR_PROMPT "minishell: "

# define ERROR_FILE_NOT_FOUND "No such file or directory\n"
# define ERROR_CMD_NOT_FOUND "command not found\n"
# define ERROR_RETRIEVING_DIR "error retrieving current directory: "
# define ERROR_CANNOT_ACCESS_PARENT "cannot access parent directories"
# define ERROR_HOME_NOT_SET "HOME not set\n"
# define ERROR_TOO_MANY_ARGS "too many arguments\n"
# define ERROR_INVALID_IDENTIFIER "not a valid identifier\n"
# define ERROR_NUMERIC_ARGUMENT "numeric argument required\n"
# define ERROR_NOT_IMPLEMENTED "Functionality not implemented, not required\n"
# define ERROR_SYNTAX "syntax error near unexpected token "
# define ERROR_TOKEN_NEWLINE "`newline'\n"
# define ERROR_TOKEN_PIPE "`|'\n"
# define ERROR_TOKEN_DOLLAR "`$'\n"
# define ERROR_UNCLOSED_QUOTES "unclosed quotes error !\n"
# define ERROR_IS_DIRECTORY "Is a directory\n"

# define HEREDOC_ORIGIN "heredoc"
# define ERROR_EXPAND_HEREDOC "failed to expand\n"
# define ERROR_F_NOT_FOUND_ORIGIN "file not found"
# define ERROR_MEMORY_ALLOCATION "memory allocation failed\n"
# define ERROR_EOF "unexpected EOF while looking for matching `"
# define ERROR_EOF_ENCLOSE "'\n"
# define ERROR_WHD "warning: here-document delimited by end-of-file (wanted `"
# define ERROR_HEREDOC_ENCLOSE "')"

# define ERROR_ORIGIN_SHELL_INIT "shell-init"
# define ERROR_ORIGIN_MAKEPATH "sh_makepath"
# define ERROR_ORIGIN_CHDIR "chdir"
# define ERROR_ORIGIN_GETCWD "getcwd: "
# define ERROR_ORIGIN_PWD "pwd"
# define ERROR_ORIGIN_EXPORT "export: `"

# define TOKEN_SIZE 64

extern volatile sig_atomic_t	g_sigint_status;

typedef enum e_rd_type
{
	RD_INPUT,
	RD_OUTPUT,
	RD_APPEND,
	RD_HEREDOC
}	t_rd_type;

typedef struct s_redirection
{
	t_rd_type				type;
	char					*file_name;
	char					*content;
	bool					expand;
	int						fd;
	int						rd_index;
	struct s_redirection	*next;
}	t_rd;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_rd			*rd_list;
	int				fd_in;
	int				fd_out;
	bool			builtin;
	int				rd_counter;
	int				rd_in_last;
	int				rd_out_last;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_sh
{
	char	*input;
	char	**pre_cmd;
	char	**envp;
	t_env	*env_list;
	t_cmd	*cmd_list;
	int		env_len;
	int		cmd_len;
	int		status;
	int		error;
	char	*cwd;
	char	*oldwd;
	int		cmd_indx;
	int		redi_indx;
	int		file_flag;
	int		cmd_flag;
}	t_sh;

// debug.c
void		print_arg_env(int argc, char **argv, char **envp);
void		print_env_list(t_env *lst);
void		print_rd_list(t_rd *lst);
void		print_cmd_list(t_sh *sh, t_cmd *lst);

// init.c
void		init_shell(t_sh *sh, char **envp);

// env_list.c
void		init_env_list(t_sh *sh);
void		add_env_entry(t_sh *sh, char *name, char *value);
t_env		*get_env_entry(t_env *env, char *name);
bool		update_env_entry(t_env *env, char *name, char *updated_value);
void		del_env_entry(t_sh *sh, char *name);

// env_util.c
char		*env_name_dup(char *envp_line, char *offset);
char		*env_value_dup(char *offset);
char		*env_list_to_envp(char *name, char *value);
void		update_envp(t_sh *sh);

// free.c
void		free_envp(char **envp);
void		free_env_list(t_sh *sh);
void		free_args(char **args);
void		free_sh(t_sh *sh);

// error.c
void		perror_exit(char *error, int rc);
void		print_shell_error(char *cmd, char *error);
void		print_shell_p_error(char *cmd, char *p_error);
void		print_cwd_error(char *origin);
int			print_syntax_error(t_sh *sh, char *token);

// signal.c
void		signal_handler_interactive(int signum);
void		signal_handler_noninteractive(int signum);

// cmd_input.c
void		input_handler(t_sh *sh);

// exec_builtin.c
void		exec_builtin(t_sh *sh, t_cmd *cmd);

// mock_util.c
// TODO: Temporary, remove when parser ready.
t_cmd		*mock_cmd(char *input);

// mock_exec.c
// TODO: Temporary, remove when parser ready.
void		mock_exec(t_sh *sh);

// cmd_builtin_env.c
int			b_env(t_sh *sh, t_cmd *cmd);

// cmd_builtin_exit.c
void		b_exit(t_sh *sh, t_cmd *cmd);

// cmd_builtin_echo.c
int			b_echo(t_sh *sh, t_cmd *cmd);

// cmd_builtin_pwd.c
int			b_pwd(t_sh *sh);

// cmd_builtin_cd.c
int			b_cd(t_sh *sh, t_cmd *cmd);

// cmd_builtin_unset.c
int			b_unset(t_sh *sh, t_cmd *cmd);

// cmd_bultin_export.c
int			b_export(t_sh *sh, t_cmd *cmd);

// cmd_builtin_export_no_arg.c
void		export_no_arg(t_sh *sh);

// cmd_path.c
char		*check_cmd_path(t_sh *sh, char *cmd);
char		*find_cmd_path(t_sh *sh, char *cmd);

// cmd_util.c
bool		is_reg(char *cmd);
bool		is_dir(char *cmd);
bool		is_exec(char *cmd);
int			ft_strcmp(const char *s1, const char *s2);
size_t		ft_strcspn(const char *str, const char *reject);

// cmd_list.c
void		add_cmd(t_sh *sh, t_cmd *cmd);
void		del_last_cmd(t_sh *sh);

// lexer.c
void		lexer(t_sh *sh);

// lexer_char_handler.c
char		*handle_charactor(char *str, int *pos);

// lexer_op_handler.c
char		*handle_operator(char *str, int *pos);
int			is_operator(char c);

// lexer_quote_handler.c
char		*handle_charactor_and_quotes(char *str, int *pos);

// lexer_space_handler.c
int			ft_isspace(char c);
void		handle_whitespaces(char *str, int *pos);

// lexer_utils.c
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);

// buf_overflow_protection.c
void		dynamic_segment_size(char ***tokens, int *token_size, int j);
void		dynamic_token_size(char **token, char *str, char *tmp);

// parser.c
void		parser(t_sh *sh);

// parser_cmd_table.c
void		parse_input(t_sh *sh);

// parser_cmd_table_utils.c
void		assign_arg(t_sh *sh, t_cmd *new_node, char *arg);
void		assign_cmd(t_sh *sh, t_cmd *new_node, char *arg);
bool		eval_builtin(char *cmd);
bool		eval_cmd(char *cmd);
bool		eval_operator(char *cmd);

// parser_quotes
char		*dequote(t_sh *sh, char *arg);

// parser_quote_utils.c
int			ft_isquotes(char c);
int			next_index_from_str(char *str, int offset, char c);
char		*substring_and_remove_quotes(char *str, int *cur, char c);
char		*insert_expand_string(char *str, char *sub_str, int pos, int cur);

// parser_redirection.c
void		assign_file(t_sh *sh, t_cmd *new_node, char *arg, int *first_flag);
void		assign_redi(t_sh *sh, t_cmd *new_node, char *str, int *first_flag);
void		eval_last_redi(t_sh *sh);

// parser_redirection_utils.c
int			count_redirection(char **args);
bool		eval_redi(char *cmd);
t_rd_type	eval_token_type(char *token);
char		*filename_handler(char *arg, int *flag, int *i);

// parser_utils.c
void		init_parser(t_sh *sh);
int			count_pointer_to_array(char **ptr);
bool		check_cmd(char *cmd, char *str);
void		safe_free(char *ptr);

// parser_free.c
void		free_double_ptr(char **ptr);
void		free_cmd_list(t_sh *sh);
void		free_redi_list(t_sh *sh);

// expander_path.c
char		*expand_path(t_sh *sh, char *org_str);

// expander_variable.c
char		*handle_dollar_sign(t_sh *sh, char *str, int *pos, int flag);
char		*expand_variable(t_sh *sh, char *env);

// syntax_analysis.c
void		chk_missing_filename(t_sh *sh, int i);
void		chk_unclosed_quotes(t_sh *sh, int *i, char c);
void		chk_empty_pipeline(t_sh *sh, int i, int len);

// exec_external.c
int			exec_command(t_sh *sh);
int			exec_commands(t_sh *sh);

// exec_external_memory.c
int			**alloc_pipe_fds(t_sh *sh);
pid_t		*alloc_pids(t_sh *sh);
void		free_pipe_fds(t_sh *sh, int **pipe_fds);

// exec_external_error.c
int			exec_cmd_error(t_sh *sh, char *full_cmd_path);
int			execve_cmd_error(t_sh *sh, char **full_cmd_path);
void		print_signal_error(int status);

// pipe.c
void		open_pipes(t_sh *sh, int **pipe_fds);
void		close_pipes(t_sh *sh, int **pipe_fds);
void		exec_piped_commands(t_sh *sh, int **pipe_fds, int i);

// redirection.c
int			check_single_redirection(t_sh *sh, t_cmd *cmd_list);
int			handle_redirections(t_sh *sh, t_cmd *cmd);
void		close_redirections(t_cmd *cmd);
void		restore_fd_std(int *fd_in, int *fd_out);

// redirection_input.c
int			rd_input_file(t_sh *sh, t_cmd *cmd, t_rd *rd);
int			rd_heredoc(t_sh *sh, t_cmd *cmd, t_rd *rd);

// redirection_output.c
int			rd_output_file(t_sh *sh, t_cmd *cmd, t_rd *rd);

// redirection_util.c
size_t		ft_strnlen(const char *s, size_t max_len);
char		*ft_strndup(const char *s, size_t n);

// redirection_heredoc.c
int			heredoc_read(t_sh *sh, t_cmd *cmd, t_rd *rd);

// redirection_heredoc_expand.c
char		*quote_expand(t_sh *sh, char *string);

// redirection_heredoc_utils.c
char		*env_value(t_sh *sh, const char *name);
char		*env_name(const char **input);
int			append_delimiter(t_rd *rd, char *line);
int			fill_heredoc(t_sh *sh, t_cmd *cmd_list);

// redirection_heredoc_error.c
void		heredoc_malloc_error(t_sh *sh);
void		delimiter_error(char *delimiter);
void		eof_error(t_sh *sh, char *token);

// child.c
void		wait_for_child(t_sh *sh, pid_t pid);
void		wait_for_children(t_sh *sh, pid_t *pids);

#endif
