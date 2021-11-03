/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/03 11:26:04 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int				g_exit_code;
int				g_interactive;

int	main(void)
{
	char	*input;
	t_exit	ext;
	t_cmd	*cmd_table;
	char	**argv;
	int		i;
	int		len_cmd_table;

	init_shell();
	while ((g_interactive = 1) && (input = readline(PROMPT)))
	{
		if (!input[0] || skip_space(input))
			continue ;
		argv = parse(input);
		if (argv == (char **)Q_ERR || argv == (char **)PIPE_ERR || \
			argv == (char **)REDIR_ERR || argv == (char **)UNEXPECTED_EOF)
			continue ;
		cmd_table = split_pipe(argv, &len_cmd_table);
		check_cmd_table(cmd_table, len_cmd_table);
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
				g_exit_code = EXECUTION_FAILURE;
			else
				exit(ext.code);
		}
		/* get builtin exit code */
		else if (ext.pid == BUILTIN && ext.code)
			g_exit_code = ext.code;
		/* get child process exit status */
		else if (WIFEXITED(ext.status) && WEXITSTATUS(ext.status))
			g_exit_code = WEXITSTATUS(ext.status);
		/* get child process exit (by signal) status */
		else if (WIFSIGNALED(ext.status))
		{
			// write(stdout_copied, "\n", 1);		//FIXME
			if (WTERMSIG(ext.status) == SIGINT)
				g_exit_code = EX_SIGINT;
			else if (WTERMSIG(ext.status) == SIGQUIT)
				g_exit_code = EX_SIGQUIT;
		}
		/* if none of above, it means cmd succeeds*/
		else
			g_exit_code = 0;						//NOTE: if execve succeed, cannot reach g_exit_code or sth
		static_stream(RESTORE);
		unlink(TMP_HD_FILE);
		add_history(input);
		free(input);
	}
	static_stream(DESTROY);
}
