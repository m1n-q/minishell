/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:14:26 by mishin            #+#    #+#             */
/*   Updated: 2021/11/22 14:30:46 by kyumlee          ###   ########.fr       */
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

# define ENV (char *)2LL
# define PIPE (char *)3LL
# define HEREDOC (char *)4LL
# define REDIRECT_IN (char *)5LL
# define REDIRECT_OUT (char *)6LL
# define REDIRECT_APPEND (char *)7LL
# define NOCMD (char *)8LL

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
int			check_and_parse(char *input, char ***ptr_argv);
int			get_cmd_table(t_cmd **ptr_cmd_table, char **argv,
				int len_cmd_table);
t_exit		run_table(t_cmd *cmd_table, int len_cmd_table);
void		check_exit(t_exit ext);
void		reset_shell(void);

/* init */
int			shell_level(void);
int			static_stream(int mode);
void		environ_to_heap(void);
int			init_shell(void);
void		lc(void);

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
int			is_equal(char *s1, char *s2);
void		exit_(int exitcode);
int			skip_space(char *s);
char		*joinjoin(char *a, char *b, char *c);
char		*join_or_dup(char *nullable, char *dupable);
char		*join_and_free(char *s1, char *s2, int tofree);
char		*dup_and_free(char *s);
intmax_t	ft_strtoimax(const char *nptr, char **endptr);
void		quick_sort(char	**arr, int start, int end);
void		free_till(int index, char **arr);
void		free_cmd_table(t_cmd *cmd_table, int len_cmd_table);
void		free_envent(t_envent entry);

void		*calloc_(size_t count, size_t size);
char		*strdup_(char *s);
char		*strjoin_(const char *s1, const char *s2);
char		*itoa_(int nbr);
char		*strlower_(char *str);

/* built-in */
int			__cd(t_cmd cmd);
int			__pwd(t_cmd cmd);
int			__env(t_cmd cmd);
int			__echo(t_cmd cmd);
int			__exit(t_cmd cmd);
int			__unset(t_cmd cmd);
int			__export(t_cmd cmd);
int			run_builtin(t_cmd cmd);
int			skip_empty_vars(t_cmd cmd, int cur);
int			is_builtin(char *arg);
int			export_internal(char *arg);

/* environ */
char		**make_tmp_environ(void);
char		*get_env_including_empty(char *arg);
char		*add_envent(char *name, char *value);
t_envent	find_envent(char *arg);
int			remove_envent(t_envent env);
void		adjust_envent(t_envent entry, char *value);

/* ************************ parse ************************ */

/* cont_pipe */
char		**cont_pipe(char **argv);

/* copy */
char		**copy_arg(char *s, char **argv, int *i, int argc);

/* copy_env */
int			copy_non_env(char *arg, char **new_arg);
int			copy_env_val(char *arg, char **new_arg, char *prev_arg);

/* copy_q */
int			copy_quotes(char *arg, char **new_arg, char *prev_arg);

/* copy_utils */
int			expand(char *s);
int			has_quotes(char *s);
int			count_env(char *arg);
char		*ambiguous_redirect_error(char *env);

/* empty_q */
char		*rm_empty_q(char *s);

/* error */
int			find_token_error(char **argv);
char		**token_error(char **argv);

/* heredoc */
int			check_delimiter(char **delim);

/* parse */
char		**parse(char *s);

/* pipe_redir */
char		*split_pipe_redir(char *s);

/* split_env */
char		**split_except_quotes(char **argv, int *i, int argc, char *raw);

/* str */
int			cnt_str_len(char *s);
char		*malloc_str(char **argv, int i, int len);

/* strs */
int			skip_q(char *s);
char		**malloc_strs(char *s, int *argc);

/* strs_utils */
int			has_leading_space(char *s);
int			has_trailing_space(char *s);
int			next_idx(char *s, int cur);
int			env_has_space(char *s, char c);

/* token */
int			is_token(char *s);
int			is_redir_token(char *s);
int			is_pipe_token(char *s);
char		*toktos(char *tok);

/* utils */
int			ft_isspace(char c);
int			is_q(char c);
int			is_pipe_redir(char c);
char		*calloc_n_lcpy(char *s, size_t dstsize);
char		*getenv_(char *s, int *i, int check);

/* ************************ parse ************************ */

/* heredoc */
int			is_heredoc(char	*s);
int			heredoc(t_cmd *cmd, char *eof);

/* redirection */
void		redir_in(t_cmd *cmd, char *file);
void		redir_out(t_cmd *cmd, char *file);
void		redir_append(t_cmd *cmd, char *file);
int			is_redir(char *arg);
int			count_redir(t_cmd *cmd);

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
void		before_exit(void);

#endif
