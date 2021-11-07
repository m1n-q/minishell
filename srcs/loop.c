/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 20:21:10 by mishin            #+#    #+#             */
/*   Updated: 2021/11/07 20:25:08 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_exit(t_exit ext)
{
	if (ext.pid == PARENT_EXIT)
	{
		if (ext.code == E2MANY) /* too many arguments => do not exit */
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
		if (WTERMSIG(ext.status) == SIGINT)
			get_or_set_exitcode(SET, EX_SIGINT);
		else if (WTERMSIG(ext.status) == SIGQUIT)
		{
			write(STDERR_FILENO, "Quit: 3", 7);
			get_or_set_exitcode(SET, EX_SIGQUIT);
		}
		write(static_stream(STDOUT), "\n", 1);
	}
	/* if none of above, it means cmd succeeds*/
	else
		get_or_set_exitcode(SET, EXECUTION_SUCCESS); // NOTE: if execve succeed, cannot reach exit_code
}

int	check_and_parse(char *input, char ***ptr_argv)
{
	char	**argv;

	if (!input[0] || skip_space(input))
		return (-1);
	argv = parse(input);
	if (argv == (char **)Q_ERR || argv == (char **)PIPE_ERR || \
		argv == (char **)REDIR_ERR || argv == (char **)UNEXPECTED_EOF)
		return (-1);
	*ptr_argv = argv;
	return (0);
}

int	get_cmd_table(t_cmd **ptr_cmd_table, char **argv, int len_cmd_table)
{
	t_cmd	*cmd_table;
	int		e;

	cmd_table = split_pipe(argv, len_cmd_table);
	e = check_cmd_table(cmd_table, len_cmd_table);
	if (e)
		return (e);
	*ptr_cmd_table = cmd_table;
	return (0);
}

t_exit	run_table(t_cmd *cmd_table, int len_cmd_table)
{
	int		i;
	t_exit	ext;

	i = -1;
	while (++i < len_cmd_table)
	{
		ext = run(cmd_table[i]);
		if (ext.pid == CHILD) /* execve failed or forked built-in */
			exit(ext.code);
	}
	return (ext);
}

void	restore_context(char *input)
{
	static_stream(RESTORE);
	unlink(TMP_HD_FILE);
	add_history(input);
	free(input);
	sig_jobcontrol(OFF);
	settty(OFF, ECHOCTL);
	get_or_set_interactive(SET, ON);
}
