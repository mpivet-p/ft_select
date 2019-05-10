/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:35:42 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/10 19:16:44 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_select			*g_head;
extern struct termios	save;

void	sigwinch_handler(int signum)
{
	(void)signum;
	signal(SIGWINCH, sigwinch_handler);
	disp_list(g_head, get_term_size() & 0xFFFF, get_maxlen(g_head));
}

void	sigint_handler(int signum)
{
	(void)signum;
	del_list(g_head);
	tcsetattr(0, TCSANOW, &save);
	tputs(tgetstr("cl", NULL), 1, ft_putscap);
	tputs(tgetstr("ve", NULL), 1, ft_putscap);
	exit(1);
}

void	sigcont_handler(int signum)
{
	(void)signum;
	term_init();
	init_keyboard(&save);
	tputs(tgetstr("vi", NULL), 1, ft_putscap);
	sigwinch_handler(SIGWINCH);
}

void	sigtstp_handler(int signum)
{
	(void)signum;
	signal(SIGINT, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, sigcont_handler);
	tputs(tgetstr("ve", NULL), 0, ft_putscap);
	tcsetattr(0, TCSANOW, &save);
	ioctl(2, TIOCSTI, "\x1A");
}
