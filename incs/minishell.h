/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:14:26 by mishin            #+#    #+#             */
/*   Updated: 2021/10/15 00:15:24 by kyumlee          ###   ########.fr       */
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

/* error */
int		puterr(int error);

/* parse */
t_cmd	parse(char *input);

/* run */
int		run(t_cmd cmd);

/* utils */
int		putchar(int c);

/* ft_split_space */
char	**ft_split_space(char *s);

/* ft_split_space_cpy */
char	*cpy_str(char *s, char *ret);

/* ft_split_space_check */
int		ft_isspace(char c);
int		check_quotes(char *s);

/* ft_split_space_str */
int		cnt_str_len(char *s);
char	*malloc_str(char *s, char **ret, int i, int len);

/* ft_split_space_strs */
char	**malloc_strs(char *s);
void	free_strs(char **ret, int i);

#endif
