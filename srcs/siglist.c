/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   siglist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:38:12 by mishin            #+#    #+#             */
/*   Updated: 2021/11/23 15:09:49 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_siglist1(char **siglist)
{
	siglist[0] = NULL;
	siglist[SIGHUP] = "Hangup";
	siglist[SIGINT] = "Interrupt";
	siglist[SIGQUIT] = "Quit";
	siglist[SIGILL] = "Illegal instruction";
	siglist[SIGTRAP] = "BPT trace/trap";
	siglist[SIGABRT] = "ABORT instruction";
	siglist[SIGEMT] = "EMT instruction";
	siglist[SIGFPE] = "Floating point exception";
	siglist[SIGKILL] = "Killed";
	siglist[SIGBUS] = "Bus error";
	siglist[SIGSEGV] = "Segmentation fault";
	siglist[SIGSYS] = "Bad system call";
	siglist[SIGPIPE] = "Broken pipe";
	siglist[SIGALRM] = "Alarm clock";
	siglist[SIGTERM] = "Terminated";
}

static void	initialize_siglist2(char **siglist)
{
	siglist[SIGURG] = "Urgent IO condition";
	siglist[SIGSTOP] = "Stopped (signal)";
	siglist[SIGTSTP] = "Stopped";
	siglist[SIGCONT] = "Continue";
	siglist[SIGCHLD] = "Child death or stop";
	siglist[SIGTTIN] = "Stopped (tty input)";
	siglist[SIGTTOU] = "Stopped (tty output)";
	siglist[SIGIO] = "I/O ready";
	siglist[SIGXCPU] = "CPU limit";
	siglist[SIGXFSZ] = "File limit";
	siglist[SIGVTALRM] = "Alarm (virtual)";
	siglist[SIGPROF] = "Alarm (profile)";
	siglist[SIGWINCH] = "Window changed";
	siglist[SIGINFO] = "Information request";
	siglist[SIGUSR1] = "User signal 1";
	siglist[SIGUSR2] = "User signal 2";
}

char	*__siglist(int mode, int sig)
{
	static char		**siglist;

	if (mode == SET)
	{
		siglist = (char **)calloc_(NSIG, sizeof(char *));
		initialize_siglist1(siglist);
		initialize_siglist2(siglist);
		return (NULL);
	}
	if (mode == GET)
		return (siglist[sig]);
	if (mode == DESTROY)
		free(siglist);
	return (NULL);
}

void	put_signame(int sig)
{
	ft_putstr_fd(__siglist(GET, sig), STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
}
