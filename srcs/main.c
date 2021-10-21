/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/22 00:48:52 by mishin           ###   ########.fr       */
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
	t_cmd	*cmd_table;
	int		stdin_copied;
	int		stdout_copied;
	char	**argv;

	int		len_cmd_table;


	stdin_copied = dup(STDIN_FILENO);
	stdout_copied = dup(STDOUT_FILENO);
	environ = environ_to_heap();						/* to modify || unset || extend and free prev */
	error = init_terminal_data();
	if (error)
		return (puterr(error));
	signal(SIGINT, sig_handler);

	int	i = -1;

	while ((input = readline(prompt)))
	{
		if (!input[0] || skip_space(input))
			continue ;

		argv = get_argv(input);
		cmd_table = split_pipe(argv, &len_cmd_table);
		i = -1;
		while (++i < len_cmd_table)
		{
			get_argv_without_redirection(check_redirection(&cmd_table[i]), &(cmd_table[i].argv));
			fill_path(&cmd_table[i]);
		}

		i = -1;
		while (++i < len_cmd_table - 1)			// except last entry
		{
			make_pipe(&cmd_table[i]);
			set_pipe_stream(&cmd_table[i], &(cmd_table[i + 1]));
		}


		i = -1;
		while (++i < len_cmd_table)
		{
			set_redir_stream(&cmd_table[i]);
			ext = run(cmd_table[i]);
			if (ext.pid == CHILD)		/* only if execve failed */
				return (ext.status);	//FIXIT: clarify name & usage: status / exitcode
		}
		// if (ext.pid != CHILD)
		// {
		// 	ext.pid = waitpid(0, &ext.status, 0);	//TODO: get exitcode of last arg
		// 	sleep(1);			//FIXIT: tmply set delay to wait print of all forked processes
		// }

		// if (ext.pid == PARENT_EXIT)	/* elif */
		// 	return (ext.status);
		// else if (ext.pid == BUILTIN && ext.status)
		// 	puterr(ext.status);
		// else if (WIFEXITED(ext.status) && WEXITSTATUS(ext.status))
		// 	puterr(WEXITSTATUS(ext.status));			/* child process exit status (not built-in func) */
		// restore_stream(stdin_copied, STDIN_FILENO);
		// restore_stream(stdout_copied, STDOUT_FILENO);
		add_history(input);
		free(input);
	}
	close(stdin_copied);
	close(stdout_copied);
}

/*
	get redir info;
	make pipe;
	connect pipe;
	set redirection;
*/
