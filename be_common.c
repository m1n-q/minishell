
/***************************************/
/*           common error              */
/***************************************/

/*
case default:
  builtin_usage ();
  return (EX_USAGE);
*/


void
builtin_usage ()
{
  if (this_command_name && *this_command_name)
    fprintf (stderr, "%s: usage: ", this_command_name);
  fprintf (stderr, "%s\n", current_builtin->short_doc);
  fflush (stderr);
}''

/* Return if LIST is NULL else barf and jump to top_level.  Used by some
   builtins that do not accept arguments. */
void
no_args (list)
     WORD_LIST *list;
{
  if (list)
    {
      builtin_error (_("too many arguments"));
      jump_to_top_level (DISCARD);
    }
}

/* Check that no options were given to the currently-executing builtin,
   and return 0 if there were options. */
int
no_options (list)
     WORD_LIST *list;
{
  reset_internal_getopt ();
  if (internal_getopt (list, "") != -1)
    {
      builtin_usage ();
      return (1);
    }
  return (0);
}

void
sh_needarg (s)
     char *s;
{
  builtin_error (_("%s: option requires an argument"), s);
}

void
sh_neednumarg (s)
     char *s;
{
  builtin_error (_("%s: numeric argument required"), s);
}

void
sh_notfound (s)
     char *s;
{
  builtin_error (_("%s: not found"), s);
}

/* Function called when one of the builtin commands detects an invalid
   option. */
void
sh_invalidopt (s)
     char *s;
{
  builtin_error (_("%s: invalid option"), s);
}

void
sh_invalidoptname (s)
     char *s;
{
  builtin_error (_("%s: invalid option name"), s);
}

void
sh_invalidid (s)
     char *s;
{
  builtin_error (_("`%s': not a valid identifier"), s);
}

void
sh_invalidnum (s)
     char *s;
{
  builtin_error (_("%s: invalid number"), s);
}

void
sh_invalidsig (s)
     char *s;
{
  builtin_error (_("%s: invalid signal specification"), s);
}

void
sh_badpid (s)
     char *s;
{
  builtin_error (_("`%s': not a pid or valid job spec"), s);
}

void
sh_readonly (s)
     const char *s;
{
  builtin_error (_("%s: readonly variable"), s);
}

void
sh_erange (s, desc)
     char *s, *desc;
{
  if (s)
    builtin_error (_("%s: %s out of range"), s, desc ? desc : _("argument"));
  else
    builtin_error (_("%s out of range"), desc ? desc : _("argument"));
}

#if defined (JOB_CONTROL)
void
sh_badjob (s)
     char *s;
{
  builtin_error (_("%s: no such job"), s);
}

void
sh_nojobs (s)
     char *s;
{
  if (s)
    builtin_error (_("%s: no job control"), s);
  else
    builtin_error (_("no job control"));
}
#endif

#if defined (RESTRICTED_SHELL)
void
sh_restricted (s)
     char *s;
{
  if (s)
    builtin_error (_("%s: restricted"), s);
  else
    builtin_error (_("restricted"));
}
#endif

void
sh_notbuiltin (s)
     char *s;
{
  builtin_error (_("%s: not a shell builtin"), s);
}

void
sh_wrerror ()
{
  builtin_error (_("write error: %s"), strerror (errno));
}

