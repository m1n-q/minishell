/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:14:26 by mishin            #+#    #+#             */
/*   Updated: 2021/10/14 13:46:31 by mishin           ###   ########.fr       */
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
# define PARENT -1
# define PARENT_EXIT -2

# define AMP 1LL
# define ENV 2LL
# define PIPE 3LL
# define HEREDOC 4LL
# define REDIRECT_IN 5LL
# define REDIRECT_OUT 6LL
# define REDIRECT_APPEND 7LL

/* error */
int			puterr(int error);

/* parse */
t_cmd		parse(char *input);

/* run */
t_exit		run(t_cmd cmd);

/* utils */
int			putchar(int c);
long long 	atonum(const char *str, int *len);

/* built-in */
int			__exit(char **argv);
int			is_builtin(char *arg);
int			run_builtin(char **argv);

/* ft_split_space_utils */
int			ft_isspace(char c);
int			cnt_s(char const *s);
int			cnt_d_q(char *s, int ret, t_cmd *cmd);
int			cnt_s_q(char *s, int ret, t_cmd *cmd);
int			cnt_s_len(char const *s, t_cmd *cmd);

/* ft_split_space */
char		**ft_split_space(char const *s, t_cmd *cmd);

/* redirection */
void		read_file(char *filename);
void		write_file(char *filename);

#endif
