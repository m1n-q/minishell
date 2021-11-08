/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/08 21:53:14 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	main(void)
{
	char	*input;
	t_exit	ext;
	t_cmd	*cmd_table;
	char	**argv;
	int		len_cmd_table;

	init_shell();
	while (1)
	{
		input = readline(PROMPT);
		if (!input)
			break ;
		if (check_and_parse(input, &argv) < 0)
			continue ;
		len_cmd_table = count_pipe(argv) + 1;
		if (get_cmd_table(&cmd_table, argv, len_cmd_table) < 0)
			continue ;
		ext = run_table(cmd_table, len_cmd_table);
		check_exit(ext);
		restore_context(input, cmd_table, len_cmd_table);
		system("leaks minishell");
	}
	static_stream(DESTROY);
	settty(RESTORE, 0);
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(get_or_set_exitcode(GET, 0));
}
