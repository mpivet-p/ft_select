/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:15:19 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/08 15:41:51 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	move_up(t_select *ptr, int maxlen)
{
	int i;

	i = ((get_term_size() & 0xFFFF) + 1) / (maxlen + 1);
	while (ptr != NULL && !(ptr->status & CURSOR))
		ptr = ptr->next;
	if (ptr != NULL)
	{
		while (i != 0 && ptr->prev != NULL)
		{
			i--;
			ptr->status &= ~CURSOR;
			ptr = ptr->prev;
		}
		ptr->status |= CURSOR;
	}
}

void	move_down(t_select *ptr, int maxlen)
{
	int i;

	i = ((get_term_size() & 0xFFFF) + 1) / (maxlen + 1);
	while (ptr != NULL && !(ptr->status & CURSOR))
		ptr = ptr->next;
	if (ptr != NULL)
	{
		while (i != 0 && ptr->next != NULL)
		{
			i--;
			ptr->status &= ~CURSOR;
			ptr = ptr->next;
		}
		ptr->status |= CURSOR;
	}
}

void	move_right(t_select *ptr)
{
	while (ptr != NULL && !(ptr->status & CURSOR))
		ptr = ptr->next;
	if (ptr != NULL && ptr->status & CURSOR)
	{
		ptr->status ^= CURSOR;
		if (ptr->next != NULL)
			ptr->next->status |= CURSOR;
		else
		{
			while (ptr != NULL && ptr->prev != NULL)
				ptr = ptr->prev;
			ptr->status |= CURSOR;
		}
	}
}

void	move_left(t_select *ptr)
{
	while (ptr != NULL && !(ptr->status & CURSOR))
		ptr = ptr->next;
	if (ptr != NULL && ptr->status & CURSOR)
	{
		ptr->status ^= CURSOR;
		if (ptr->prev != NULL)
			ptr->prev->status |= CURSOR;
		else
		{
			while (ptr != NULL && ptr->next != NULL)
				ptr = ptr->next;
			ptr->status |= CURSOR;
		}
	}
}
