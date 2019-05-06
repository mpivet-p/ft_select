/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:59:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/06 00:08:01 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select	*global_head;

int		get_term_size(void)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return ((w.ws_row << 16) + w.ws_col);
}

void	debug_key(char *buffer)
{
	ft_putnbr(buffer[0]);
	ft_putchar('|');
	ft_putnbr(buffer[1]);
	ft_putchar('|');
	ft_putnbr(buffer[2]);
	ft_putchar('|');
	ft_putnbr(buffer[3]);
	ft_putchar('|');
	ft_putnbr(buffer[4]);
	ft_putstr("\n\r");
}

int		get_keystrokes(char *buffer, t_select *ptr)
{
	if (ft_strcmp("\x1b", buffer) == 0 || ptr == NULL)
		return (-1);
	if (ft_strcmp("\n", buffer) == 0)
		return (1);
	if (ft_strcmp(" ", buffer) == 0)
		list_select(ptr);
	else if (buffer[0] == 127 && buffer[1] == 0)
		ft_putstr("del\n");
	else if (ft_strcmp("\x1B[A", buffer) == 0)
		ft_putstr("up\n");
	else if (ft_strcmp("\x1b[B", buffer) == 0)
		ft_putstr("down\n");
	else if (ft_strcmp("\x1b[D", buffer) == 0)
		move_left(ptr);
	else if (ft_strcmp("\x1b[C", buffer) == 0)
		move_right(ptr);
//		ft_putstr("right\n");
	else if (ptr)
		debug_key(buffer);
	return (0);
}

int		read_loop(t_select *head)
{
	char	buffer[4 + 1];
	int		key;
	int		ret;

	ft_bzero(buffer, 5);
	ret = 0;
	while ((ret = read(0, buffer, 4)))
	{
		buffer[ret] = 0;
		key = get_keystrokes(buffer, head);
		if (key == -1 || key == 1)
			return (key);
			disp_list(head, get_term_size() & 0xFFFF);
		ft_strclr(buffer);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int				ret_term;
	int				ret;
	t_select		*head;
	struct termios	init;
	struct termios	save;

	ret_term = term_init();
	ret = 0;
	if (init_keyboard(&init, &save) == 0)
	{
		if (argc < 2)
			ft_putstr_fd("usage: ft_select [arg1 arg2 ...]", 2);
		else if (ret_term == 0)
		{
			tputs(tgetstr("vi", NULL), 1, ft_putscap);
			head = create_list(argv);
			global_head = head;
			sigwinch_handler(SIGWINCH);
			ret = read_loop(head);
			tputs(tgetstr("cl", NULL), 1, ft_putscap);
			tputs(tgetstr("ve", NULL), 1, ft_putscap);
			if (ret == 1)
				print_result(head);
			head = del_list(head);
		}
	}
	tcsetattr(0, TCSANOW, &save);
	return (0);
}
