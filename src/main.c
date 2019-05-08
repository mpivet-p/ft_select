/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:59:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/08 20:19:38 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select		*global_head;
struct termios	save;

int		get_term_size(void)
{
	struct winsize	w;

	ioctl(2, TIOCGWINSZ, &w);
	return ((w.ws_row << 16) + w.ws_col);
}

int		get_keystrokes(char *buffer, t_select **head, int *maxlen)
{
	t_select *ptr;

	ptr = *head;
	if (ft_strcmp("\x1b", buffer) == 0 || ptr == NULL)
		return (-1);
	if (ft_strcmp("\n", buffer) == 0)
		return (1);
	if (ft_strcmp(" ", buffer) == 0)
		list_select(ptr);
	else if (buffer[0] == 127 && buffer[1] == 0)
	{
		*head = remove_list(ptr);
		global_head = *head;
		*maxlen = get_maxlen(*head);
	}
	else if (ft_strcmp("\x1B[A", buffer) == 0)
		move_up(ptr, *maxlen);
	else if (ft_strcmp("\x1b[B", buffer) == 0)
		move_down(ptr, *maxlen);
	else if (ft_strcmp("\x1b[D", buffer) == 0)
		move_left(ptr);
	else if (ft_strcmp("\x1b[C", buffer) == 0)
		move_right(ptr);
	else
		return (2);
	return (0);
}

int		read_loop(t_select **head)
{
	char	buffer[4 + 1];
	int		key;
	int		maxlen;
	int		ret;

	ft_bzero(buffer, 5);
	ret = 0;
	maxlen = get_maxlen(*head);
	while ((ret = read(0, buffer, 4)) && *head != NULL)
	{
		buffer[ret] = 0;
		key = get_keystrokes(buffer, head, &maxlen);
		if (key == -1 || key == 1)
			return (key);
		if (key == 0)
			disp_list(*head, get_term_size() & 0xFFFF, maxlen);
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

	ret_term = term_init();
	ret = 0;
	if (init_keyboard(&init, &save) == 0)
	{
		if (argc < 2)
			ft_putstr_fd("usage: ft_select [arg1] [arg2] ...", 2);
		else if (ret_term == 0)
		{
			tputs(tgetstr("vi", NULL), 1, ft_putscap);
			head = create_list(argv);
			global_head = head;
			sigwinch_handler(SIGWINCH);
			ret = read_loop(&head);
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
