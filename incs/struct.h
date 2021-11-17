/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:06:50 by mishin            #+#    #+#             */
/*   Updated: 2021/11/17 20:38:24 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_io_table
{
	int		in;
	int		out;
	int		err;
}				t_io_table;

typedef struct s_cmd
{
	char			*path;
	char			**argv;
	int				argc;
	int				pipe[2];
	int				any_err;
	t_io_table		redir_stream;
	t_io_table		pipe_stream;
}			t_cmd;

typedef struct s_exit
{
	int	pid;
	int	status;
	int	code;
}				t_exit;

typedef struct s_envent
{
	char	*name;
	char	*value;
	char	*string;
	int		index;
}				t_envent;

typedef struct s_var
{
	char	*name;
	char	*value;
}				t_var;

typedef struct s_cut
{
	uintmax_t	off;
	int			lim;
}				t_cut;

typedef struct s_result
{
	uintmax_t	acc;
	int			any;
	int			neg;
}				t_result;

#endif
