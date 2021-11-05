/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:11:26 by mishin            #+#    #+#             */
/*   Updated: 2021/11/05 21:59:52 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* term_buffer is Nullable? */
int	init_terminal_data(void)
{
	char	*termtype;
	int		error;
	char	term_buffer[2048];

	termtype = getenv("TERM");
	if (termtype == NULL)
		return (ENOTERMENV);
	error = tgetent(term_buffer, termtype);
	if (error == 0)
		return (ENOTERMENT);
	if (error < 0)
		return (ENOTERMINFO);
	return (0);
}

void	settty(int mode, unsigned long flag)
{
	static TTY	save;
	static TTY	t;

	if (mode == SAVE)
	{
		tcgetattr(STDIN_FILENO, &save);
		tcgetattr(STDIN_FILENO, &t);
	}
	if (flag && mode == OFF)
	{
		t.c_lflag &= ~flag;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}
	else if (flag && mode == ON)
	{
		t.c_lflag |= flag;
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}
	else if (mode == RESTORE)
		tcsetattr(STDIN_FILENO, TCSANOW, &save);
}
