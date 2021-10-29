

/*****************************************************/
/*					export error                     */
/*****************************************************/

/* For each variable name in LIST, make that variable appear in the
   environment passed to simple commands.  If there is no LIST, then
   print all such variables.  An argument of `-n' says to remove the
   exported attribute from variables named in LIST.  An argument of
  -f indicates that the names present in LIST refer to functions. */
int export_builtin(list)
register WORD_LIST *list;
{
  return (set_or_show_attributes(list, att_exported, 0));
}

/* For each variable name in LIST, make that variable have the specified
   ATTRIBUTE.  An arg of `-n' says to remove the attribute from the the
   remaining names in LIST (doesn't work for readonly). */
int set_or_show_attributes(list, attribute, nodefs)
register WORD_LIST *list;
int attribute, nodefs;
{
  register SHELL_VAR *var;
  int assign, undo, functions_only, arrays_only, any_failed, assign_error, opt;
  int aflags;
  char *name;

  undo = functions_only = arrays_only = any_failed = assign_error = 0;

  if (list)
  {
    while (list)
    {
      name = list->word->word;

      //NOTE: get assign pos
      assign = assignment(name, 0);


      //NOTE: set append flag
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

      //NOTE: check idenfier for just "name" part
      if (legal_identifier(name) == 0)
      {
        sh_invalidid(name);
        if (assign)\
          assign_error++;
        else
          any_failed++;
        list = list->next;
        continue;
      }


      //NOTE: restore string to org, after check name
      if (assign) /* xxx [-np] name=value */
      {
        name[assign] = '=';
        if (aflags & ASS_APPEND)
          name[assign - 1] = '+';

        /* This word has already been expanded once with command
     and parameter expansion.  Call do_assignment_no_expand (),
     which does not do command or parameter substitution.  If
     the assignment is not performed correctly, flag an error. */
        if (do_assignment_no_expand(name) == 0)
          assign_error++;
        name[assign] = '\0';
        if (aflags & ASS_APPEND)
          name[assign - 1] = '\0';
      }

      set_var_attribute(name, attribute, undo);
      list = list->next;
    }
  }

  return (assign_error ? EX_BADASSIGN
                       : ((any_failed == 0) ? EXECUTION_SUCCESS
                                            : EXECUTION_FAILURE));
}

