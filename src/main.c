/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:59:38 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/10 22:33:56 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select		*g_head;
struct termios	save;

int		get_term_size(void)
{
	struct winsize	w;

	ioctl(2, TIOCGWINSZ, &w);
	return ((w.ws_row << 16) + w.ws_col);
}

int		enough_space(int maxlen)
{
	int			size;
	int			cols;
	t_select	*ptr;

	ptr = g_head;
	size = 0;
	cols = ((get_term_size() & 0xFFFF) + 1) / (maxlen + 1);
	while (ptr != NULL)
	{
		size++;
		ptr = ptr->next;
	}
	if (size > (int)(cols * (get_term_size() >> 16)))
		return (-1);
	return (0);
}

int		get_keystrokes(char *buffer, t_select **head, int *maxlen)
{
	t_select *ptr;

	ptr = *head;
	if (ft_strcmp(" ", buffer) == 0)
		list_select(ptr);
	else if ((buffer[0] == 127 && buffer[1] == 0)
			|| ft_strcmp("\x1B[3~", buffer) == 0)
	{
		*head = remove_list(ptr);
		g_head = *head;
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
	int		maxlen;
	int		ret;

	ft_bzero(buffer, 5);
	ret = 0;
	maxlen = get_maxlen(*head);
	while ((ret = read(0, buffer, 4)) && *head != NULL)
	{
		buffer[ret] = 0;
		if (ft_strcmp("\x1b", buffer) == 0)
			return (-1);
		if (ft_strcmp("\n", buffer) == 0)
			return (1);
		if (enough_space(maxlen) == 0)
			if (get_keystrokes(buffer, head, &maxlen) == 0)
				disp_list(*head, get_term_size() & 0xFFFF, maxlen);
		if (*head == NULL)
			return (0);
		ft_strclr(buffer);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	int				ret_term;
	int				ret;
	t_select		*head;

	ret_term = term_init();
	ret = 0;
	if (argc < 2)
		ft_putstr_fd("usage: ft_select [arg1] [arg2] ...", 2);
	if (ret_term != 0 || init_keyboard(&save) != 0
			|| !(head = create_list(argv)))
		return (0);
	tputs(tgetstr("vi", NULL), 1, ft_putscap);
	ft_putstr_fd("\033[?1049h\033[H", 2);
	g_head = head;
	sigwinch_handler(SIGWINCH);
	ret = read_loop(&head);
	tputs(tgetstr("cl", NULL), 1, ft_putscap);
	tputs(tgetstr("ve", NULL), 1, ft_putscap);
	if (ret == 1)
		print_result(head);
	head = del_list(head);
	tcsetattr(0, TCSANOW, &save);
	ft_putstr_fd("\033[?1049l", 2);
	return (0);
}
