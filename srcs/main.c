/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/11/22 15:38:48 by kyumlee          ###   ########.fr       */
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


	// int i = -1;
	// char	**s = split2("ls -l\" ls -l \"\"abc\"");
	// while (s[++i])
	// 	printf("[%s]\n", s[i]);
	// printf("[%s]\n", strdup_wo_q(s[1]));

	init_shell();
	while (1)
	{
		input = readline(PROMPT);
		lc();
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
		system("leaks minishell -quiet");
	}
	before_exit();
	system("leaks minishell -quiet");
	exit(get_or_set_exitcode(GET, 0));
}
