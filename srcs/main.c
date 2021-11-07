/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/07 20:25:18 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	t_exit	ext;
	t_cmd	*cmd_table;
	char	**argv;
	int		len_cmd_table;

	init_shell();
	while ((input = readline(PROMPT)))
	{
		if (check_and_parse(input, &argv) < 0)
			continue ;
		len_cmd_table = count_pipe(argv) + 1;
		if (get_cmd_table(&cmd_table, argv, len_cmd_table) < 0)
			continue ;
		ext = run_table(cmd_table, len_cmd_table);
		check_exit(ext);
		restore_context(input);
	}
	static_stream(DESTROY);
	settty(RESTORE, 0);
	write(STDERR_FILENO, "exit\n", 5);
	exit(get_or_set_exitcode(GET, 0));
}
