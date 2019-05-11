/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 18:35:42 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/11 15:49:47 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_select			*g_head;
extern struct termios	g_save;

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
	tcsetattr(0, TCSANOW, &g_save);
	tputs(tgetstr("cl", NULL), 1, ft_putscap);
	tputs(tgetstr("ve", NULL), 1, ft_putscap);
	exit(1);
}

void	sigcont_handler(int signum)
{
	(void)signum;
	term_init();
	init_keyboard(&g_save);
	tputs(tgetstr("vi", NULL), 1, ft_putscap);
	ft_putstr_fd("\033[?1049h\033[H", 2);
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
	tcsetattr(0, TCSANOW, &g_save);
	ioctl(2, TIOCSTI, "\x1A");
	ft_putstr_fd("\033[?1049l", 2);
}
