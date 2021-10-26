/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:41:49 by mishin            #+#    #+#             */
/*   Updated: 2021/10/26 21:42:07 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	if (list && list->word && ISOPTION (list->word->word, '-'))
		list = list->next;
*/
int __exit(char **argv)
{
	long long	exit_code;
	int			len;

	// if (argc > 2)							/* have to know argc */
	// 	return ();								/* exit: too many arguments => it does not exit */
	exit_code = 0LL;
	if (argv[1])
	{
		exit_code = atonum(argv[1], &len);
		if (exit_code == NON_NUMERIC)			/* exit: string: numeric argument required */
		{
			puterr(ENONUM);
			// g_exit_code = (unsigned char)-1;
			return (-1);
		}
	}
	// g_exit_code = (int)exit_code;
	return ((int)exit_code);
}
