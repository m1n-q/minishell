/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:14:26 by mishin            #+#    #+#             */
/*   Updated: 2021/10/13 19:06:41 by mishin           ###   ########.fr       */
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
# include "readline/readline.h"
# include "readline/history.h"
# include "libft.h"
# include "myerror.h"
# include "struct.h"

# define PROMPT "\e[1;46mminishell\e[0m "
# define BUILTIN -4242
# define CHILD 0
# define PARENT -1
# define PARENT_EXIT -2
# define NON_NUMERIC -4444444444LL

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

/* ft_split_space */
char		**ft_split_space(char const *s);
#endif
