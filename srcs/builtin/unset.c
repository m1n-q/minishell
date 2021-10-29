/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:42:54 by mishin            #+#    #+#             */
/*   Updated: 2021/10/28 20:14:19 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	if (var && !unset_function && non_unsettable_p (var))
		builtin_error (_("%s: cannot unset"), name);
	if (var && readonly_p (var))
		builtin_error (_("%s: cannot unset: readonly %s", name, unset_function ? "function" : "variable")

	=> no (readonly || non_unsettable) var in minishell.
*/

int	__unset(char **argv)
{
	t_envent	env;
	int			i;

	if (argv[1])
	{
		if (isoption(argv[1], TIL_END))
		{
			sh_invalidopt(argv[0], argv[1]);	/* do not allow any option */
			return (EXECUTION_FAILURE);
		}
	}
	i = 0;
	while (argv[++i])
	{
		env = find_envent(argv[i]);
		remove_envent(env);
	}
	return (0);
}



/*****************************************************/
/*					unset error                      */
/*****************************************************/

// int
// unset_builtin (list)
//   WORD_LIST *list;
// {
//   int unset_function, unset_variable, unset_array, opt, any_failed;
//   char *name;

//   unset_function = unset_variable = unset_array = any_failed = 0;

//   reset_internal_getopt ();
//   while ((opt = internal_getopt (list, "fv")) != -1)
//     {
//       switch (opt)
// 	{
// 	case 'f':
// 	  unset_function = 1;
// 	  break;
// 	case 'v':
// 	  unset_variable = 1;
// 	  break;
// 	default:
// 	  builtin_usage ();
// 	  return (EX_USAGE);
// 	}
//     }

//   list = loptend;

//   while (list)
//     {
//       SHELL_VAR *var;
//       int tem;

//       name = list->word->word;

//       /* Bash allows functions with names which are not valid identifiers
// 	 to be created when not in posix mode, so check only when in posix
// 	 mode when unsetting a function. */
//       if (legal_identifier (name) == 0)
// 	{
// 	  sh_invalidid (name);
// 	  NEXT_VARIABLE ();
// 	}

//       var = unset_function ? find_function (name) : find_variable (name);

//       if (var && !unset_function && non_unsettable_p (var))
// 	{
// 	  builtin_error (_("%s: cannot unset"), name);
// 	  NEXT_VARIABLE ();
// 	}

//       /* Posix.2 says that unsetting readonly variables is an error. */
//       if (var && readonly_p (var))
// 	{
// 	  builtin_error (_("%s: cannot unset: readonly %s"),
// 			 name, unset_function ? "function" : "variable");
// 	  NEXT_VARIABLE ();
// 	}

//       list = list->next;
//     }

//   return (any_failed ? EXECUTION_FAILURE : EXECUTION_SUCCESS);
// }
