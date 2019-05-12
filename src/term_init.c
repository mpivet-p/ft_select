/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:35:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/12 17:26:27 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		term_init(void)
{
	char	*termtype;
	int		ret;

	ret = 0;
	if ((termtype = getenv("TERM")) == NULL)
	{
		ft_putstr_fd("ft_select: TERM not set.\n", 2);
		return (-1);
	}
	ret = tgetent(NULL, termtype);
	if (ret == 0)
		ft_putstr_fd("Terminal type is not defined.\n", 2);
	if (ret == -1 || !(tgetstr("cl", NULL)) || !(tgetstr("vi", NULL))
			|| !(tgetstr("us", NULL)) || !(tgetstr("me", NULL))
			|| !(tgetstr("mr", NULL)))
	{
		ft_putstr_fd("Terminal not supported.\n", 2);
		ret = -1;
	}
	if (ret == -1 || ret == 0)
		return (-1);
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigtstp_handler);
	return (0);
}

int		init_keyboard(struct termios *save)
{
	struct termios	init;

	tcgetattr(0, &(*save));
	init = *save;
	init.c_lflag &= ~(ICANON);
	init.c_lflag &= ~(ECHO);
	init.c_cc[VMIN] = 1;
	init.c_cc[VTIME] = 0;
	return (tcsetattr(0, TCSADRAIN, &init));
}
