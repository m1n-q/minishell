/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:40:55 by mishin            #+#    #+#             */
/*   Updated: 2021/11/09 18:01:14 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	The env utility exits 0 on success, and >0
     if an error occurs.  An exit status of 126
     indicates that utility was found, but could
     not be executed.  An exit status of 127
     indicates that utility could not be found.

	 => not builtin!

	 명령을 찾을 수 없는 경우 해당 명령을 실행하기 위해 생성된 자식 프로세스는 상태 127을 반환합니다.
	명령을 찾았지만 실행할 수 없는 경우 반환 상태는 126입니다.
*/
int	__env(char **argv)
{
	int			i;
	t_envent	entry;

	if (argv[1])
	{
		if (isoption(argv[1], TIL_END))
		{
			sh_invalidopt(argv[0], argv[1]);
			builtin_usage(argv[0], ENV_SHORTDOC);
			return (EXECUTION_FAILURE);
		}
		else
		{
			builtin_usage(argv[0], ENV_SHORTDOC);
			return (EX_BADUSAGE);
		}
	}
	i = -1;
	while (environ[++i])
	{
		entry = find_envent(environ[i]);
		if (getenv(entry.name))
			printf("%s\n", environ[i]);
		free_envent(entry);
	}
	return (0);
}
