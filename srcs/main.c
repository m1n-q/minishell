/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:21:38 by mishin            #+#    #+#             */
/*   Updated: 2021/10/12 20:25:43 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

char	term_buffer[2048];
char	*prompt = PROMPT;

int	init_terminal_data(void)
{
	char	*termtype;
	int		error;

	termtype = getenv("TERM");
	if (termtype == NULL)
		return (ENOTERMENV);
	error = tgetent(term_buffer, termtype); 	/* term_buffer is Nullable? */
	if (error == 0)
		return (ENOTERMENT);
	if (error < 0)
		return (ENOTERMINFO);
	return (0);
}

int	main()
{
	char	*input;
	int		error;

	error = init_terminal_data();
	if (error)
		return (puterr(error));
	while ((input = readline(prompt)))
	{
		if (!run(parse(input)))
			return (0);
		add_history(input);
		free(input);
	}
}
