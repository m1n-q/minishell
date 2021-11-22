/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/11/22 22:23:19 by kyumlee          ###   ########.fr       */
=======
/*   Updated: 2021/11/22 22:36:20 by mishin           ###   ########.fr       */
>>>>>>> c910b26b819ca744133bc366575d7d0d2fff83c5
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
<<<<<<< HEAD
		lc();
=======
		dummy_lc();
>>>>>>> c910b26b819ca744133bc366575d7d0d2fff83c5
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
<<<<<<< HEAD
	before_exit();
	exit(get_or_set_exitcode(GET, 0));
=======
	ft_putendl_fd("exit", STDERR_FILENO);
	exit_(get_or_set_exitcode(GET, 0));
>>>>>>> c910b26b819ca744133bc366575d7d0d2fff83c5
}
