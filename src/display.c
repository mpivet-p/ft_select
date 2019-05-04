/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:34:46 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/04 21:37:47 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	disp_link(t_select *ptr, int maxlen, int spaces)
{
	int		i;

	i = maxlen - ft_strlen(ptr->name);
	if (tgetstr("us", NULL) != NULL && ptr->status & CURSOR)
		tputs(tgetstr("us", NULL), 1, ft_putchar);
	if (tgetstr("mr", NULL) != NULL && ptr->status & SELECTED)
		tputs(tgetstr("mr", NULL), 1, ft_putchar);
	ft_putstr(ptr->name);
	if (ptr->status & CURSOR || ptr->status & SELECTED)
		tputs(tgetstr("me", NULL), 1, ft_putchar);
	while (spaces != 0 && i--)
		ft_putchar(' ');

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

void	disp_list(t_select *ptr, int width)
{
	int		cols;
	int		maxlen;
	int		i;

	i = 0;
	maxlen = get_maxlen(ptr);
	cols = (width + 1) / (maxlen + 1);
	tputs(tgetstr("cl", NULL), 2, ft_putchar);
	while (ptr != NULL)
	{
		if (ptr->next == NULL || i + 1 == cols)
			disp_link(ptr, maxlen, 0);
		else
			disp_link(ptr, maxlen, i + 1 - cols);
		if (++i == cols || ptr->next == NULL)
		{
			ft_putchar(10);
			i = 0;
		}
		else
			ft_putchar(' ');
		ptr = ptr->next;
	}
}
