/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myerror.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mishin <mishin@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:14:47 by mishin            #+#    #+#             */
/*   Updated: 2021/10/14 19:59:14 by mishin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYERROR_H
# define MYERROR_H

# define ENOTERMENV			-4	/* Specify a termtype with $TERM */
# define ENOTERMENT			-5	/* No such terminal entry */
# define ENOTERMINFO		-6	/* Cannot find terminfo database */
# define ENOCMD				-10	/* Command not found */
# define ENONUM				-11	/* Numeric argument required */
# define E2MANY				-12	/* Too many arguments */

#endif
