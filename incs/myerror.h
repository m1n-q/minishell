/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myerror.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:14:47 by mishin            #+#    #+#             */
/*   Updated: 2021/11/17 18:41:42 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYERROR_H
# define MYERROR_H

# define EXECUTION_FAILURE	1
# define EXECUTION_SUCCESS	0

# define ENOTERMENV			-4	/* Specify a termtype with $TERM */
# define ENOTERMENT			-5	/* No such terminal entry */
# define ENOTERMINFO		-6	/* Cannot find terminfo database */
# define ENONUM				-11	/* Numeric argument required */
# define E2MANY				-12	/* Too many arguments */

/* Usage messages by builtins result in a return status of 2. */
# define EX_BADUSAGE		2

/* Special exit statuses used by the shell, internally and externally. */
# define EX_BINARY_FILE		126
# define EX_NOEXEC			126
# define EX_NOINPUT			126
# define EX_NOTFOUND		127

# define EX_SIGINT			130
# define EX_SIGQUIT			131

# define EX_SHERRBASE		256	/* all special error values are > this. */

# define EX_BADSYNTAX		257	/* shell syntax error */
# define EX_USAGE			258	/* syntax error in usage */
# define EX_REDIRFAIL		259	/* redirection failed */
# define EX_BADASSIGN		260	/* variable assignment error */
# define EX_EXPFAIL			261	/* word expansion failed */

# define Q_ERR				(char **)1LL
# define REDIR_ERR			(char **)2LL
# define PIPE_ERR			(char **)3LL
# define UNEXPECTED_EOF		(char **)4LL
# define INVALID_REDIR		(char **)5LL
# define AMBIG_REDIR		(char **)9LL

# define CD_SHORTDOC			"cd [dir]"
# define ENV_SHORTDOC			"env"
# define PWD_SHORTDOC			"pwd"
# define ECHO_SHORTDOC			"echo [-n] [arg ...]"
# define EXIT_SHORTDOC			"exit [n]"
# define UNSET_SHORTDOC			"unset [name ...]"
# define EXPORT_SHORTDOC		"export [name[=value] ...]"

# define HEREDOC_INTR		-42
# define FDERR				-1
# define FORKERR			-24
# define MALLOCERR			-22
#endif
