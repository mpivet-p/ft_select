/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 19:35:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/05 21:56:48 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		term_init(void)
{
	char *termtype;
	int ret;

	termtype = getenv("TERM");
	ret = 0;
	if (termtype == NULL)
	{
		ft_putstr_fd("ft_select: TERM not set.\n", 2);
		return (-1);
	}
	ret = tgetent(NULL, termtype);
	if (ret == -1)
	{
		ft_putstr_fd("Could not access the termcap database.\n", 2);
		return (-1);
	}
	if (ret == 0)
	{
		ft_putstr_fd("Terminal type is not defined.\n", 2);
		return (-1);
	}
	return (0);
}

int		init_keyboard(struct termios *init, struct termios *save)
{
	tcgetattr(0, &(*save));
	*init = *save;
	init->c_lflag &= ~(ICANON);
	init->c_lflag &= ~(ECHO);
	init->c_cc[VMIN] = 1;
	init->c_cc[VTIME] = 0;
	return (tcsetattr(0, TCSADRAIN, &(*init)));
}
