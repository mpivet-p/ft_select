/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 22:09:46 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/08 20:18:29 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_select			*global_head;
extern struct termios	save;

void	sigwinch_handler(int signum)
{
	(void)signum;
	signal(SIGWINCH, sigwinch_handler);
	disp_list(global_head, get_term_size() & 0xFFFF, get_maxlen(global_head));
}

void	sigint_handler(int signum)
{
	(void)signum;
	del_list(global_head);
	tcsetattr(0, TCSANOW, &save);
	tputs(tgetstr("cl", NULL), 1, ft_putscap);
	tputs(tgetstr("ve", NULL), 1, ft_putscap);
	exit(1);
}
