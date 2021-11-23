/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 15:30:55 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../incs/minishell.h"

int	main(void)
{
	char	*input;
	t_exit	ext;
	t_cmd	*cmd_table;
	int		len_cmd_table;
	char	**argv;

	init_shell();
	while (1)
	{
		input = readline(PROMPT);
		dummy_lc();
		if (!input)
			break ;
		if (check_and_parse(input, &argv) < 0)
			continue ;
		len_cmd_table = count_pipe(argv) + 1;
		if (get_cmd_table(&cmd_table, argv, len_cmd_table) < 0)
			continue ;
		ext = run_table(cmd_table, len_cmd_table);
		free_cmd_table(cmd_table, len_cmd_table);
		check_exit(ext);
		reset_shell();
	}
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_(get_or_set_exitcode(GET, 0));
}
