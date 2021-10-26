

/*****************************************************/
/*					echo error                       */
/*****************************************************/

int
echo_builtin (list)
     WORD_LIST *list;
{
  int display_return, do_v9, i, len;
  char *temp, *s;

  do_v9 = xpg_echo;
  display_return = 1;

  if (posixly_correct && xpg_echo)
    goto just_echo;

  for (; list && (temp = list->word->word) && *temp == '-'; list = list->next)
    {
      /* If it appears that we are handling options, then make sure that
	 all of the options specified are actually valid.  Otherwise, the
	 string should just be echoed. */
      temp++;

      for (i = 0; temp[i]; i++)
	{
	  if (strchr (VALID_ECHO_OPTIONS, temp[i]) == 0)
	    break;
	}

      /* echo - and echo -<nonopt> both mean to just echo the arguments. */
      if (*temp == 0 || temp[i])
	break;

      /* All of the options in TEMP are valid options to ECHO.
	 Handle them. */
      while (i = *temp++)
	{
	  switch (i)
	    {
	    case 'n':
	      display_return = 0;
	      break;
#if defined (V9_ECHO)
	    case 'e':
	      do_v9 = 1;
	      break;
	    case 'E':
	      do_v9 = 0;
	      break;
#endif /* V9_ECHO */
	    default:
	      goto just_echo;	/* XXX */
	    }
	}
    }

just_echo:

  clearerr (stdout);	/* clear error before writing and testing success */

  while (list)
    {
      i = len = 0;
      temp = do_v9 ? ansicstr (list->word->word, STRLEN (list->word->word), 1, &i, &len)
		   : list->word->word;
      if (temp)
	{
	  if (do_v9)
	    {
	      for (s = temp; len > 0; len--)
		putchar (*s++);
	    }
	  else
	    printf ("%s", temp);
#if defined (SunOS5)
	  fflush (stdout);	/* Fix for bug in SunOS 5.5 printf(3) */
#endif
	}
      if (do_v9 && temp)
	free (temp);
      list = list->next;
      if (i)
	{
	  display_return = 0;
	  break;
	}
      if (list)
	putchar(' ');
    }

  if (display_return)
    putchar ('\n');
  fflush (stdout);
  if (ferror (stdout))
    {
      sh_wrerror ();
      clearerr (stdout);
      return (EXECUTION_FAILURE);
    }
  return (EXECUTION_SUCCESS);
}



/*****************************************************/
/*					pwd error                        */
/*****************************************************/

int
pwd_builtin (list)
     WORD_LIST *list;
{
  char *directory;
  int opt, pflag;

  verbatim_pwd = no_symbolic_links;
  pflag = 0;
  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "LP")) != -1)
    {
      switch (opt)
	{
	case 'P':
	  verbatim_pwd = pflag = 1;
	  break;
	case 'L':
	  verbatim_pwd = 0;
	  break;
	default:
	  builtin_usage ();
	  return (EXECUTION_FAILURE);
	}
    }
  list = loptend;

#define tcwd the_current_working_directory

  directory = tcwd ? (verbatim_pwd ? sh_physpath (tcwd, 0) : tcwd)
		   : get_working_directory ("pwd");

  /* Try again using getcwd() if canonicalization fails (for instance, if
     the file system has changed state underneath bash). */
  if ((tcwd && directory == 0) ||
      (posixly_correct && same_file (".", tcwd, (struct stat *)0, (struct stat *)0) == 0))
    directory = resetpwd ("pwd");

#undef tcwd

  if (directory)
    {
      printf ("%s\n", directory);
      /* This is dumb but posix-mandated. */
      if (posixly_correct && pflag)
	setpwd (directory);
      if (directory != the_current_working_directory)
	free (directory);
      fflush (stdout);
      if (ferror (stdout))
	{
	  sh_wrerror ();
	  clearerr (stdout);
	  return (EXECUTION_FAILURE);
	}

      return (EXECUTION_SUCCESS);
    }
  else
    return (EXECUTION_FAILURE);
}


/*****************************************************/
/*			     	env error                       * /
/*****************************************************/
/*****************************************************/
/*					unset error                      */
/*****************************************************/

int
unset_builtin (list)
  WORD_LIST *list;
{
  int unset_function, unset_variable, unset_array, opt, any_failed;
  char *name;

  unset_function = unset_variable = unset_array = any_failed = 0;

  reset_internal_getopt ();
  while ((opt = internal_getopt (list, "fv")) != -1)
    {
      switch (opt)
	{
	case 'f':
	  unset_function = 1;
	  break;
	case 'v':
	  unset_variable = 1;
	  break;
	default:
	  builtin_usage ();
	  return (EX_USAGE);
	}
    }

  list = loptend;

  if (unset_function && unset_variable)
    {
      builtin_error (_("cannot simultaneously unset a function and a variable"));
      return (EXECUTION_FAILURE);
    }

  while (list)
    {
      SHELL_VAR *var;
      int tem;
#if defined (ARRAY_VARS)
      char *t;
#endif

      name = list->word->word;

#if defined (ARRAY_VARS)
      unset_array = 0;
      if (!unset_function && valid_array_reference (name))
	{
	  t = strchr (name, '[');
	  *t++ = '\0';
	  unset_array++;
	}
#endif

      /* Bash allows functions with names which are not valid identifiers
	 to be created when not in posix mode, so check only when in posix
	 mode when unsetting a function. */
      if (((unset_function && posixly_correct) || !unset_function) && legal_identifier (name) == 0)
	{
	  sh_invalidid (name);
	  NEXT_VARIABLE ();
	}

      var = unset_function ? find_function (name) : find_variable (name);

      if (var && !unset_function && non_unsettable_p (var))
	{
	  builtin_error (_("%s: cannot unset"), name);
	  NEXT_VARIABLE ();
	}

      /* Posix.2 says that unsetting readonly variables is an error. */
      if (var && readonly_p (var))
	{
	  builtin_error (_("%s: cannot unset: readonly %s"),
			 name, unset_function ? "function" : "variable");
	  NEXT_VARIABLE ();
	}

      /* Unless the -f option is supplied, the name refers to a variable. */
#if defined (ARRAY_VARS)
      if (var && unset_array)
	{
	  if (array_p (var) == 0)
	    {
	      builtin_error (_("%s: not an array variable"), name);
	      NEXT_VARIABLE ();
	    }
	  else
	    {
	      tem = unbind_array_element (var, t);
	      if (tem == -1)
		any_failed++;
	    }
	}
      else
#endif /* ARRAY_VARS */
      tem = unset_function ? unbind_func (name) : unbind_variable (name);

      /* This is what Posix.2 draft 11+ says.  ``If neither -f nor -v
	 is specified, the name refers to a variable; if a variable by
	 that name does not exist, a function by that name, if any,
	 shall be unset.'' */
      if (tem == -1 && !unset_function && !unset_variable)
	tem = unbind_func (name);

      /* SUSv3, POSIX.1-2001 say:  ``Unsetting a variable or function that
	 was not previously set shall not be considered an error.'' */

      if (unset_function == 0)
	stupidly_hack_special_variables (name);

      list = list->next;
    }

  return (any_failed ? EXECUTION_FAILURE : EXECUTION_SUCCESS);
}





/*****************************************************/
/*					export error                     */
/*****************************************************/


/* For each variable name in LIST, make that variable appear in the
   environment passed to simple commands.  If there is no LIST, then
   print all such variables.  An argument of `-n' says to remove the
   exported attribute from variables named in LIST.  An argument of
  -f indicates that the names present in LIST refer to functions. */
int
export_builtin (list)
     register WORD_LIST *list;
{
  return (set_or_show_attributes (list, att_exported, 0));
}

int
set_or_show_attributes (list, attribute, nodefs)
     register WORD_LIST *list;
     int attribute, nodefs;
{
  register SHELL_VAR *var;
  int assign, undo, functions_only, arrays_only, any_failed, assign_error, opt;
  int aflags;
  char *name;
#if defined (ARRAY_VARS)
  WORD_LIST *nlist, *tlist;
  WORD_DESC *w;
#endif

  undo = functions_only = arrays_only = any_failed = assign_error = 0;
  /* Read arguments from the front of the list. */
  reset_internal_getopt ();
  while ((opt = internal_getopt (list, ATTROPTS)) != -1)
    {
      switch (opt)
	{
	  case 'n':
	    undo = 1;
	    break;
	  case 'f':
	    functions_only = 1;
	    break;
#if defined (ARRAY_VARS)
	  case 'a':
	     arrays_only = 1;
	     break;
#endif
	  case 'p':
	    break;
	  default:
	    builtin_usage ();
	    return (EX_USAGE);
	}
    }
  list = loptend;

  if (list)
    {
      if (attribute & att_exported)
	array_needs_making = 1;

      /* Cannot undo readonly status, silently disallowed. */
      if (undo && (attribute & att_readonly))
	attribute &= ~att_readonly;

      while (list)
	{
	  name = list->word->word;

	  if (functions_only)		/* xxx -f name */
	    {
	      var = find_function (name);
	      if (var == 0)
		{
		  builtin_error (_("%s: not a function"), name);
		  any_failed++;
		}
	      else
		SETVARATTR (var, attribute, undo);

	      list = list->next;
	      continue;
	    }

	  /* xxx [-np] name[=value] */
	  assign = assignment (name, 0);

	  aflags = 0;
	  if (assign)
	    {
	      name[assign] = '\0';
	      if (name[assign - 1] == '+')
		{
		  aflags |= ASS_APPEND;
		  name[assign - 1] = '\0';
		}
	    }

	  if (legal_identifier (name) == 0)
	    {
	      sh_invalidid (name);
	      if (assign)
		assign_error++;
	      else
		any_failed++;
	      list = list->next;
	      continue;
	    }

	  if (assign)	/* xxx [-np] name=value */
	    {
	      name[assign] = '=';
	      if (aflags & ASS_APPEND)
		name[assign - 1] = '+';
#if defined (ARRAY_VARS)
	      /* Let's try something here.  Turn readonly -a xxx=yyy into
		 declare -ra xxx=yyy and see what that gets us. */
	      if (arrays_only)
		{
		  tlist = list->next;
		  list->next = (WORD_LIST *)NULL;
		  w = make_word ("-ra");
		  nlist = make_word_list (w, list);
		  opt = declare_builtin (nlist);
		  if (opt != EXECUTION_SUCCESS)
		    assign_error++;
		  list->next = tlist;
		  dispose_word (w);
		  free (nlist);
		}
	      else
#endif
	      /* This word has already been expanded once with command
		 and parameter expansion.  Call do_assignment_no_expand (),
		 which does not do command or parameter substitution.  If
		 the assignment is not performed correctly, flag an error. */
	      if (do_assignment_no_expand (name) == 0)
		assign_error++;
	      name[assign] = '\0';
	      if (aflags & ASS_APPEND)
		name[assign - 1] = '\0';
	    }

	  set_var_attribute (name, attribute, undo);
	  list = list->next;
	}
    }
  else
    {
      SHELL_VAR **variable_list;
      register int i;

      if ((attribute & att_function) || functions_only)
	{
	  variable_list = all_shell_functions ();
	  if (attribute != att_function)
	    attribute &= ~att_function;	/* so declare -xf works, for example */
	}
      else
	variable_list = all_shell_variables ();

#if defined (ARRAY_VARS)
      if (attribute & att_array)
	{
	  arrays_only++;
	  if (attribute != att_array)
	    attribute &= ~att_array;
	}
#endif

      if (variable_list)
	{
	  for (i = 0; var = variable_list[i]; i++)
	    {
#if defined (ARRAY_VARS)
	      if (arrays_only && array_p (var) == 0)
		continue;
#endif
	      if ((var->attributes & attribute))
		show_var_attributes (var, READONLY_OR_EXPORT, nodefs);
	    }
	  free (variable_list);
	}
    }

  return (assign_error ? EX_BADASSIGN
		       : ((any_failed == 0) ? EXECUTION_SUCCESS
  					    : EXECUTION_FAILURE));
}

/* Show the attributes for shell variable VAR.  If NODEFS is non-zero,
   don't show function definitions along with the name.  If PATTR is
   non-zero, it indicates we're being called from `export' or `readonly'.
   In POSIX mode, this prints the name of the calling builtin (`export'
   or `readonly') instead of `declare', and doesn't print function defs
   when called by `export' or `readonly'. */
int
show_var_attributes (var, pattr, nodefs)
     SHELL_VAR *var;
     int pattr, nodefs;
{
  char flags[8], *x;
  int i;

  i = 0;

  /* pattr == 0 means we are called from `declare'. */
  if (pattr == 0 || posixly_correct == 0)
    {
#if defined (ARRAY_VARS)
      if (array_p (var))
	flags[i++] = 'a';
#endif

      if (function_p (var))
	flags[i++] = 'f';

      if (integer_p (var))
	flags[i++] = 'i';

      if (readonly_p (var))
	flags[i++] = 'r';

      if (trace_p (var))
	flags[i++] = 't';

      if (exported_p (var))
	flags[i++] = 'x';
    }
  else
    {
#if defined (ARRAY_VARS)
      if (array_p (var))
	flags[i++] = 'a';
#endif

      if (function_p (var))
	flags[i++] = 'f';
    }

  flags[i] = '\0';

  /* If we're printing functions with definitions, print the function def
     first, then the attributes, instead of printing output that can't be
     reused as input to recreate the current state. */
  if (function_p (var) && nodefs == 0 && (pattr == 0 || posixly_correct == 0))
    {
      printf ("%s\n", named_function_string (var->name, function_cell (var), 1));
      nodefs++;
      if (pattr == 0 && i == 1 && flags[0] == 'f')
	return 0;		/* don't print `declare -f name' */
    }

  if (pattr == 0 || posixly_correct == 0)
    printf ("declare -%s ", i ? flags : "-");
  else if (i)
    printf ("%s -%s ", this_command_name, flags);
  else
    printf ("%s ", this_command_name);

#if defined (ARRAY_VARS)
 if (array_p (var))
    print_array_assignment (var, 1);
  else
#endif
  /* force `readonly' and `export' to not print out function definitions
     when in POSIX mode. */
  if (nodefs || (function_p (var) && pattr != 0 && posixly_correct))
    printf ("%s\n", var->name);
  else if (function_p (var))
    printf ("%s\n", named_function_string (var->name, function_cell (var), 1));
  else if (invisible_p (var))
    printf ("%s\n", var->name);
  else
    {
      x = sh_double_quote (var_isset (var) ? value_cell (var) : "");
      printf ("%s=%s\n", var->name, x);
      free (x);
    }
  return (0);
}





