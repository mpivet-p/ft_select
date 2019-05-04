/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:59:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/04 21:50:47 by mpivet-p         ###   ########.fr       */
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

int		get_term_size(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return ((w.ws_row << 16) + w.ws_col);
}

void	move_cursor(int x, int y)
{
	char *cm_cap;

	cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, x, y), 2, ft_putchar);
}

void	init_keyboard(struct termios *init, struct termios *save)
{
	tcgetattr(0, &(*save));
	*init = *save;
	init->c_lflag &= ~ICANON;
	init->c_lflag &= ~ECHO;
	init->c_cc[VMIN] = 1;
	init->c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &(*init));
}

int		main(int argc, char **argv)
{
	int				ret_term;
	t_select		*head;
	int				size;
	struct termios	init;
	struct termios	save;

	ret_term = term_init();
	init_keyboard(&init, &save);
	size = 0;
	if (argc < 2)
		ft_putstr_fd("usage: ft_select [arg1 arg2 ...]", 2);
	else if (ret_term == 0)
	{
		tputs(tgetstr("vi", NULL), 2, ft_putchar);
		head = create_list(argv);
		while (1)
		{
			if ((size & 0xFFFF) != (get_term_size() & 0xFFFF))
			{
				size = get_term_size();
				disp_list(head, size & 0xFFFF);
			}
		}
		tputs(tgetstr("ve", NULL), 2, ft_putchar);
		head = del_list(head);
	}
	tcsetattr(0, TCSANOW, &save);
	return (0);
}




//	if (ret_term == 0)
//	{
//		while ((ret = read(0, buffer, 4)) != -1)
//		{
//			i = -1;
//			buffer[ret] = 0;
//			if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 65)
//				ft_putstr("up\n");
//			else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 66)
//				ft_putstr("down\n");
//			else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 67)
//				ft_putstr("right\n");
//			else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 68)
//				ft_putstr("left\n");
//			else if (buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 72)
//			{
//				printf("%i || %i\n", get_term_size() >> 16, get_term_size() & 0xFFFF);
//				fflush(stdin);
//			}
//			else if (buffer[0] == 3 || (buffer[0] == 27 && buffer[1] == 0))
//				break ;
//			else
//			{
//				ft_putnbr(buffer[0]);
//				ft_putnbr(buffer[1]);
//				ft_putnbr(buffer[2]);
//				ft_putnbr(buffer[3]);
//				ft_putchar('\n');
//			}
//			ft_strclr(buffer);
//		}
//	}
