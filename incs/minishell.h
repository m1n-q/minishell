/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:14:26 by mishin            #+#    #+#             */
/*   Updated: 2021/11/07 20:24:56 by mishin           ###   ########.fr       */
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
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include "readline/readline.h"
# include "readline/history.h"
# include "libft.h"
# include "myerror.h"
# include "struct.h"

# define PROMPT "\e[1;46mminishell\e[0m "
# define TMP_HD_FILE "/tmp/minishell_heredoc_file"

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
# define NOCMD 8LL

# define TIL_SEC 0
# define TIL_END 1

# define DUPLCTE 0
# define RESTORE 1
# define DESTROY 2
# define STDOUT 3

# define GET 0
# define SET 1
# define SAVE 5
# define ON 1
# define OFF 0

# define DEFAULT -2

extern char	**environ;


/* main loop */
int		check_and_parse(char *input, char ***ptr_argv);
int		get_cmd_table(t_cmd **ptr_cmd_table, char **argv, int len_cmd_table);
t_exit	run_table(t_cmd *cmd_table, int len_cmd_table);
void	check_exit(t_exit ext);
void	restore_context(char *input);

/* init */
int			shell_level(void);
int			static_stream(int mode);
char		**environ_to_heap(void);
int			init_shell(void);

/* term */
void		settty(int mode, unsigned long flag);
int			init_terminal_data(void);

/* put error msg */
int			puterr(int error);
void		file_error(char *command);
void		internal_error(char *command, char *err_string);
int			builtin_error(char *command, char *arg, char *message, int optflag);
char		**syntax_error(char **error, char *token, int exit_code);

/* check error */
int			check_error(char *command);

/* run */
t_exit		run(t_cmd cmd);

/* utils */
int			get_argc(char **argv);
void		free_till(int index, char **arr);
int			is_equal(char *s1, char *s2);
int			skip_space(char *s);
char		*joinjoin(char *a, char *b, char *c);
intmax_t	ft_strtoimax(const char *nptr, char **endptr);
void		quick_sort(char	**arr, int start, int end);

/* built-in */
int			__cd(char **argv);
int			__pwd(char **argv);
int			__env(char **argv);
int			__echo(char **argv);
int			__exit(char **argv);
int			__unset(char **argv);
int			__export(char **argv);
int			is_builtin(char *arg);
int			run_builtin(char **argv);
int			export_internal(char *arg);

/* environ */
char		**make_tmp_environ(void);
char		*get_env_including_empty(char *arg);
int			add_envent(char *name, char *value);
t_envent	find_envent(char *arg);
int			remove_envent(t_envent env);

/* ************************ parse ************************ */
/* parse */
char		**parse(char *s);

/* error */
int			is_pipe_err(char **argv, int i);
int			is_double_pipe_err(char **argv);
char		**redir_err(char **argv, int i);

/* heredoc */
char		*add_q_to_heredoc_del(char *s);

/* empty_q.c */
char		*rm_empty_q(char *s);

/* copy */
char		*cpy_str(char *s, char **argv, int *i);

/* env */
char		*case_env(char *s, char tok);

/* pipe_redir */
void		cnt_pipe_redir(char *s, int *cnt);
char		*split_pipe_redir(char *s);

/* str */
int			cnt_str_len(char *s);
char		*malloc_str(char *s, char **argv, int i, int len);

/* strs */
int			skip_q(char *s);
char		**malloc_strs(char *s);
void		free_strs(char **argv, int i);

/* utils */
int			ft_isspace(char c);
int			is_q(char c);
int			is_pipe_rin_rout(char c);
int			is_empty_q(char *s);
int			has_q(char *s);

/* cont_pipe */
char		**cont_pipe(char **argv);
/* ************************ parse ************************ */

/* heredoc */
int			is_heredoc(char	*s);
int			heredoc(t_cmd *cmd, char *eof);

/* redirection */
void		redir_in(t_cmd *cmd, char *file);
void		redir_out(t_cmd *cmd, char *file);
void		redir_append(t_cmd *cmd, char *file);

/* pipe */
int			count_pipe(char	**argv);
t_cmd		*split_pipe(char **argv, int len_cmd_table);
int			make_pipe(t_cmd *cmd);
int			set_pipe_stream(t_cmd *cmd, t_cmd *next);

/* stream */
int			connect_stream(t_io_table stream);
int			destroy_stream(t_io_table stream);
int			restore_stream(int std_copied, int std_org);

/* path */
int			set_path(t_cmd *cmd);

/* cmd */
int			check_cmd_table(t_cmd *cmd_table, int len_cmd_table);

/* signal */
void		sig_handler_interactive(int sig);
void		sigstop_handler(int sig);
void		sigcont_handler(int sig);
void		sig_jobcontrol(int mode);
void		set_sighandlers(void);

/* islegal */
int			legal_variable_starter(char c);
int			legal_variable_char(char c);
int			legal_identifier(char *name);
int			legal_number(char *string, intmax_t *result);

/* variable */
t_var		unbind_var(char *arg, int *aflag);
char		*bind_var(t_var var, int assign_pos, int *aflag);
int			get_assign_pos(const char *string);

/* getter */
int			get_or_set_exitcode(int mode, int val);
int			get_or_set_interactive(int mode, int val);

/* not categoried yet */
void		sh_neednumarg(char *command, char *s);
void		sh_invalidid(char *command, char *s);
void		sh_invalidopt(char *command, char *opt);
char		*sh_double_quote(char *string);
void		builtin_usage(char *command, char *usage);
int			isoption(char *s, int optlen);

#endif
