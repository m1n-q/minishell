/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 20:21:10 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 15:34:26 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

void	check_exit(t_exit ext)
{
	int	sig;

	if (ext.pid == PARENT_EXIT)
	{
		if (ext.code == E2MANY)
			get_or_set_exitcode(SET, EXECUTION_FAILURE);
		else
			exit_(ext.code);
	}
	else if (ext.pid == BUILTIN && ext.code)
		get_or_set_exitcode(SET, ext.code);
	else if (WIFEXITED(ext.status) && WEXITSTATUS(ext.status))
		get_or_set_exitcode(SET, WEXITSTATUS(ext.status));
	else if (WIFSIGNALED(ext.status))
	{
		sig = WTERMSIG(ext.status);
		get_or_set_exitcode(SET, 128 + sig);
		if (sig != SIGINT)
			put_signame(sig);
		ft_putendl_fd("", static_stream(STDOUT));
	}
	else
		get_or_set_exitcode(SET, EXECUTION_SUCCESS);
}

int	check_and_parse(char *input, char ***ptr_argv)
{
	char	**argv;

	if (!input[0] || skip_space(input))
	{
		free(input);
		return (-1);
	}
	add_history(input);
	argv = parse(input);
	if (argv == Q_ERR || argv == PIPE_ERR || \
		argv == REDIR_ERR || argv == UNEXPECTED_EOF || \
		argv == INVALID_REDIR || argv == AMBIG_REDIR)
		return (-1);
	*ptr_argv = argv;
	return (0);
}

int	get_cmd_table(t_cmd **ptr_cmd_table, char **argv, int len_cmd_table)
{
	t_cmd	*cmd_table;
	int		e;

	cmd_table = split_pipe(argv, len_cmd_table);
	free_till(get_argc(argv), argv);
	free(argv);
	e = check_cmd_table(cmd_table, len_cmd_table);
	if (e)
	{
		free_cmd_table(cmd_table, len_cmd_table);
		return (e);
	}
	*ptr_cmd_table = cmd_table;
	return (0);
}

/* line 91: execve failed | forked built-in */
t_exit	run_table(t_cmd *cmd_table, int len_cmd_table)
{
	int		i;
	t_exit	ext;
	t_exit	last;

	i = -1;
	while (++i < len_cmd_table)
	{
		ext = run(cmd_table[i]);
		if (ext.pid == CHILD)
			exit(ext.code);
		if (i == len_cmd_table - 1)
			last = ext;
	}
	ext.pid = waitpid(-1, &ext.status, WUNTRACED);
	while (ext.pid > 0)
	{
		if (WIFSTOPPED(ext.status))
			nojobcontrol(&ext);
		if (ext.pid == last.pid)
			last.status = ext.status;
		ext.pid = waitpid(-1, &ext.status, WUNTRACED);
	}
	return (last);
}

void	reset_shell(void)
{
	static_stream(RESTORE);
	unlink(TMP_HD_FILE);
	sig_jobcontrol(OFF);
	settty(OFF, ECHOCTL);
	get_or_set_interactive(SET, ON);
}
