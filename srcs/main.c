/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/21 00:56:14 by mishin           ###   ########.fr       */
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

int	skip_space(char *s)
{
	while (ft_isspace(*s))
		s++;
	if (!*s)
		return (1);
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

	int		len_cmd_table;

	stdin_copied = dup(STDIN_FILENO);
	stdout_copied = dup(STDOUT_FILENO);
	environ = environ_to_heap();						/* to modify || unset || extend and free prev */
	error = init_terminal_data();
	if (error)
		return (puterr(error));
	signal(SIGINT, sig_handler);





	int	i = -1;

	while ((input = readline(prompt)) && (i = -1))
	{
		if (!input[0] || skip_space(input))
			continue ;

		argv = get_argv(input);
		cmd_table = split_pipe(argv, &len_cmd_table);
		while (++i < len_cmd_table)
		{
			// printf("%d : %s\n", i, cmd_table[i].argv[0]);
			get_argv_without_redirection(check_redirection(cmd_table[i]), &(cmd_table[i].argv));
			fill_path(&cmd_table[i]);
		}


		// printf("get argv w/o redir: %s\n", cmd_table[0].argv[0]);
		i = -1;
		while (++i < len_cmd_table)
		{
			// printf("cmd_table[%d].argv[0] %s\n",i, cmd_table[0].argv[0]);
			ext = run(cmd_table[i]);
		}


		// ext = run(parse(input));
		if (ext.pid == CHILD)
			return (ext.status);
		else if (ext.pid == PARENT_EXIT)
			return (ext.status);
		else if (ext.pid == BUILTIN && ext.status)
			puterr(ext.status);
		else if (WIFEXITED(ext.status) && WEXITSTATUS(ext.status))
			puterr(WEXITSTATUS(ext.status));			/* child process exit status (not built-in func) */
		restore_stream(stdin_copied, STDIN_FILENO);
		restore_stream(stdout_copied, STDOUT_FILENO);
		add_history(input);
		free(input);
	}
	close(stdin_copied);
	close(stdout_copied);
}
