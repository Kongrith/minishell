/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: <rvesterl@student.42bangkok.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:23:28 by rvesterl          #+#    #+#             */
/*   Updated: 2025/03/25 12:02:46 by rvesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <signal.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "libft/libft.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#define SHELL_PROMPT "minishell$ "

typedef struct s_cmd
{
	char *cmd;
	char **args;
	struct s_cmd *next;
} t_cmd;

typedef struct s_env
{
	char *name;
	char *value;
	struct s_env *next;
} t_env;

typedef struct s_sh
{
	char *input;
	char **envp;
	t_env *env_list;
	size_t env_len;
	int status;
} t_sh;

// debug.c
void print_arg_env(int argc, char **argv, char **envp);
void print_env_list(t_env *lst);

// init.c
void init_shell(t_sh *sh, char **envp);

// env_list.c
void init_env_list(t_sh *sh);
void update_envp(t_sh *sh);
void add_env_list(t_sh *sh, char *name, char *value);
t_env *get_env(t_env *env, char *name);

// env_util.c
char *env_name_dup(char *envp_line, char *offset);
char *env_value_dup(char *offset);
char *env_list_to_envp(char *name, char *value);

// free.c
void free_envp(char **envp);
void free_env_list(t_sh *sh);

// error.c
void perror_exit(char *error, int rc);

// signal.c
void handle_sigint(int signum);

#endif
