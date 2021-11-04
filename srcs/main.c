/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/04 16:19:58 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	t_exit	ext;
	t_cmd	*cmd_table;
	char	**argv;
	int		i;
	int		len_cmd_table;

	init_shell();
	while ((input = readline(PROMPT)))
	{
		if (!input[0] || skip_space(input))
			continue ;
		argv = parse(input);
		if (argv == (char **)Q_ERR || argv == (char **)PIPE_ERR || \
			argv == (char **)REDIR_ERR || argv == (char **)UNEXPECTED_EOF)
			continue ;

		len_cmd_table = count_pipe(argv) + 1;
		cmd_table = split_pipe(argv, len_cmd_table);
		if (check_cmd_table(cmd_table, len_cmd_table) == HEREDOC_INTR)
			continue ;
		i = -1;
		while (++i < len_cmd_table)
		{
			ext = run(cmd_table[i]);
			if (ext.pid == CHILD)					/* execve failed or forked built-in */
				exit(ext.code);
		}
		if (ext.pid == PARENT_EXIT)
		{
			if (ext.code == E2MANY)					/* too many arguments => do not exit */
				get_or_set_exitcode(SET, EXECUTION_FAILURE);
			else
				exit(ext.code);
		}
		/* get builtin exit code */
		else if (ext.pid == BUILTIN && ext.code)
			get_or_set_exitcode(SET, ext.code);
		/* get child process exit status */
		else if (WIFEXITED(ext.status) && WEXITSTATUS(ext.status))
			get_or_set_exitcode(SET, WEXITSTATUS(ext.status));
		/* get child process exit (by signal) status */
		else if (WIFSIGNALED(ext.status))
		{
			write(static_stream(STDOUT), "\n", 1);
			if (WTERMSIG(ext.status) == SIGINT)
				get_or_set_exitcode(SET, EX_SIGINT);
			else if (WTERMSIG(ext.status) == SIGQUIT)
				get_or_set_exitcode(SET, EX_SIGQUIT);
		}
		/* if none of above, it means cmd succeeds*/
		else
			get_or_set_exitcode(SET, EXECUTION_SUCCESS);						//NOTE: if execve succeed, cannot reach exit_code
		static_stream(RESTORE);
		unlink(TMP_HD_FILE);
		add_history(input);
		free(input);
		get_or_set_interactive(SET, ON);
	}
	static_stream(DESTROY);
}
