/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/14 19:58:48 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	term_buffer[2048];
char	*prompt = PROMPT;

int	init_terminal_data(void)
{
	char	*termtype;
	int		error;

	termtype = getenv("TERM");
	if (termtype == NULL)
		return (ENOTERMENV);
	error = tgetent(term_buffer, termtype); 	/* term_buffer is Nullable? */
	if (error == 0)
		return (ENOTERMENT);
	if (error < 0)
		return (ENOTERMINFO);
	return (0);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

int	main()
{
	char	*input;
	int		error;
	t_exit	ext;

	error = init_terminal_data();
	if (error)
		return (puterr(error));
	signal(SIGINT, sig_handler);
	while ((input = readline(prompt)))
	{
		if (!input[0])
			continue ;
		ext = run(parse(input));
		if (ext.pid == CHILD)
			return (ext.status);
		else if (ext.pid == PARENT_EXIT)
			return (ext.status);
		else if (ext.pid == BUILTIN && ext.status)
			puterr(ext.status);
		else if (WIFEXITED(ext.status) && WEXITSTATUS(ext.status))
			puterr(WEXITSTATUS(ext.status));			/* child process exit status (not built-in func) */

		add_history(input);
		free(input);
	}
}
