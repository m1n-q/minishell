/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/22 22:58:52 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char		term_buffer[2048];
char		*prompt = PROMPT;

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




int	main()
{
	char	*input;
	int		error;
	t_exit	ext;
	t_cmd	*cmd_table;
	int		stdin_copied;
	int		stdout_copied;
	char	**argv;
	int		i;
	int		len_cmd_table;


	TTY	org_setting;
	TTY	my_setting;
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &org_setting);
		tcgetattr(STDIN_FILENO, &my_setting);

		my_setting.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &my_setting);
	}

	stdin_copied = dup(STDIN_FILENO);
	stdout_copied = dup(STDOUT_FILENO);
	environ = environ_to_heap();					/* to modify || unset || extend and free prev */
	error = init_terminal_data();
	if (error)
		return (puterr(error));
	// signal(SIGINT, sig_handler);
	signal(SIGINT, sig_handler_parent);
	signal(SIGQUIT, SIG_IGN);

	while ((input = readline(prompt)))
	{
		if (!input[0] || skip_space(input))
			continue ;

		argv = get_argv(input);
		cmd_table = split_pipe(argv, &len_cmd_table);
		check_cmd_table(cmd_table, len_cmd_table);

		i = -1;
		while (++i < len_cmd_table)
		{
			ext = run(cmd_table[i]);
			if (ext.pid == CHILD)					/* only if execve failed */
				return (ext.status);				//FIXIT: clarify name & usage: status / exitcode
		}
		if (ext.pid == PARENT_EXIT)
			return (ext.status);
		else if (ext.pid == BUILTIN && ext.status)
			puterr(ext.status);
		else if (WIFEXITED(ext.status) && WEXITSTATUS(ext.status))
			puterr(WEXITSTATUS(ext.status));		/* child process exit status (not built-in func) */
		// else if (WIFSIGNALED(ext.status))
		// 	printf("signal : %d\n", WTERMSIG(ext.status));
		restore_stream(stdin_copied, STDIN_FILENO);
		restore_stream(stdout_copied, STDOUT_FILENO);
		add_history(input);
		free(input);
	}
	close(stdin_copied);
	close(stdout_copied);

	tcsetattr(STDIN_FILENO, TCSANOW, &org_setting);
}

