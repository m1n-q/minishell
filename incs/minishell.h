/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:14:26 by mishin            #+#    #+#             */
/*   Updated: 2021/10/25 16:54:28 by kyumlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "libft.h"
# include "myerror.h"
# include "struct.h"

# define NON_NUMERIC -4444444444LL
# define PROMPT "\e[1;46mminishell\e[0m "

# define CHILD 0
# define BUILTIN -1
# define PARENT_EXIT -2

# define AMP 1LL
# define ENV 2LL
# define PIPE 3LL
# define HEREDOC 4LL
# define REDIRECT_IN 5LL
# define REDIRECT_OUT 6LL
# define REDIRECT_APPEND 7LL

extern char	**environ;

/* error */
int			puterr(int error);

/* parse */
char		**get_argv(char *input);
t_cmd		parse(char *input);

/* run */
t_exit		run(t_cmd cmd);

/* utils */
int			putchar(int c);
int			get_argc(char **argv);
long long 	atonum(const char *str, int *len);
void		free_till(int index, char **arr);
int			is_equal(char *s1, char *s2);
int			skip_space(char *s);

/* built-in */
int			__exit(char **argv);
int			is_builtin(char *arg);
int			run_builtin(char **argv);

/* environ */
char		**environ_to_heap(void);
int			check_arg(char *arg);
int			__unset(char **argv);
char		*get_env_including_empty(char *arg);
int			append_envent(char *arg);
t_envent	get_envent(char *arg);
int			print_including_empty(void);

/* ft_split_space */
char		**ft_split_space(char *s);

/* ft_split_space_cpy */
char		*cpy_str(char *s, char *ret);

/* ft_split_space_env */
char		*case_env(char *s);

/* ft_split_space_pipe_redir */
void		cnt_pipe_redir(char *s, int *cnt);
char		*split_pipe_redir(char *s);

/* ft_split_space_str */
int			cnt_str_len(char *s);
char		*malloc_str(char *s, char **ret, int i, int len);

/* ft_split_space_strs */
int			skip_q(char *s);
char		**malloc_strs(char *s);
void		free_strs(char **ret, int i);

/* ft_split_space_utils */
int			ft_isspace(char c);
int			is_q(char c);
int			is_pipe_rin_rout(char c);
int			is_empty_q(char *s);
int			has_q(char *s);

/* redirection */
int			redir_in(char *arg);
int			redir_out(char *arg);
int			redir_append(char *arg);
int			check_redir(t_cmd *cmd, int *count_redir);
int			trim_redir(char ***argv, int count_redir);

/* pipe */
int			count_pipe(char	**argv);
t_cmd		*split_pipe(char **argv, int *size);
int			make_pipe(t_cmd *cmd);
int			set_pipe_stream(t_cmd *cmd, t_cmd *next);

/* stream */
int			connect_stream(t_io_table stream);
int			destroy_stream(t_io_table stream);
int			restore_stream(int std_copied, int std_org);

/* path */
char		**get_paths(void);
int			set_path(t_cmd *cmd);

/* cmd */
int			check_cmd_table(t_cmd *cmd_table, int len_cmd_table);
#endif
