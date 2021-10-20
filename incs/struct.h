/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:06:50 by mishin            #+#    #+#             */
/*   Updated: 2021/10/20 17:30:06 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_io_table
{
	int		stdin_fd;
	int		stdout_fd;
	int		stderr_fd;
}				t_io_table;

typedef struct s_cmd
{
	char			*path;
	char			**argv;
	int				d_q;
	int				s_q;
	int				r_in;
	int				r_out;
	int				here_doc;
	int				r_out_a;
	t_io_table		io_table;
}			t_cmd;

typedef struct s_exit
{
	int	pid;
	int	status;
}				t_exit;

typedef struct s_envent
{
	char	*name;
	char	*string;		//FIXIT: query is better?
	int		index;
}				t_envent;

#endif
