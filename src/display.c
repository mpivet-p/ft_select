/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:34:46 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/08 16:42:54 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	disp_link(t_select *ptr, int maxlen, int spaces)
{
	int		i;

	i = maxlen - ft_strlen(ptr->name);
	if (tgetstr("us", NULL) != NULL && ptr->status & CURSOR)
		tputs(tgetstr("us", NULL), 2, ft_putscap);
	if (tgetstr("mr", NULL) != NULL && ptr->status & SELECTED)
		tputs(tgetstr("mr", NULL), 2, ft_putscap);
	ft_putstr_fd(ptr->name, 2);
	if (ptr->status & CURSOR || ptr->status & SELECTED)
		tputs(tgetstr("me", NULL), 2, ft_putscap);
	while (spaces != 0 && i--)
		ft_putchar_fd(' ', 2);

}

void	print_result(t_select *head)
{
	int		i;

	i = 0;
	while (head != NULL)
	{
		if (head->status & SELECTED)
		{
			if (i++ != 0)
				ft_putchar(' ');
			ft_putstr(head->name);
		}
		head = head->next;
	}
	if (i != 0)
		ft_putchar('\n');
}

int		get_maxlen(t_select *ptr)
{
	int		size;
	int		c;

	size = 0;
	c = 0;
	while (ptr != NULL)
	{
		if ((c = ft_strlen(ptr->name)) > size)
			size = c;
		ptr = ptr->next;
	}
	return (size);
}

void	disp_list(t_select *ptr, int width, int maxlen)
{
	int		cols;
	int		i;

	i = 0;
	cols = (width + 1) / (maxlen + 1);
	tputs(tgetstr("cl", NULL), 2, ft_putscap);
	while (ptr != NULL)
	{
		if (ptr->next == NULL || i + 1 == cols)
			disp_link(ptr, maxlen, 0);
		else
			disp_link(ptr, maxlen, i + 1 - cols);
		if (++i == cols || ptr->next == NULL)
		{
			ft_putchar_fd('\n', 2);
			i = 0;
		}
		else
			ft_putchar_fd(' ', 2);
		ptr = ptr->next;
	}
}
