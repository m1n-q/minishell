/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/09 15:40:08 by mishin           ###   ########.fr       */
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
		restore_context(cmd_table, len_cmd_table);
	}
	before_exit();
	// system("leaks minishell -quiet");
	exit(get_or_set_exitcode(GET, 0));
}
