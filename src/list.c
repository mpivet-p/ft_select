/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 16:03:59 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/09 17:45:13 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_select	*newlink(char *name, t_select *head)
{
	t_select	*newlink;

	if (!(newlink = (t_select*)malloc(sizeof(t_select))))
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	head->next = newlink;
	newlink->prev = head; 
	newlink->next = NULL;
	newlink->status = 0;
	if (!(newlink->name = ft_strdup(name)))
		return (NULL);
	return (head);
}

t_select	*remove_list(t_select *head)
{
	t_select	*ptr;

	ptr = head;
	while (ptr != NULL && !(ptr->status & CURSOR))
		ptr = ptr->next;
	move_right(head);
	if (ptr == head)
		head = head->next;
	if (ptr != NULL)
	{
		if (ptr->prev != NULL)
			ptr->prev->next = ptr->next;
		if (ptr->next != NULL)
			ptr->next->prev = ptr->prev;
		ft_strdel(&(ptr->name));
		free(ptr);
	}
	return (head);
}

void	list_select(t_select *ptr)
{
	t_select	*head;

	head = ptr;
	while (ptr && !(ptr->status & CURSOR))
		ptr = ptr->next;
	if (ptr->status & CURSOR)
	{
		ptr->status ^= SELECTED;
		move_right(head);
	}
}	

t_select	*del_list(t_select *head)
{
	t_select	*next;

	while (head != NULL)
	{
		next = head->next;
		ft_strdel(&(head->name));
		free(head);
		head = next;
	}
	return (NULL);
}

t_select	*create_list(char **argv)
{
	int		i;
	t_select *head;

	i = 2;
	if (!(head = (t_select*)malloc(sizeof(t_select))))
		return (NULL);
	head->next = NULL;
	head->prev = NULL;
	if (!(head->name = ft_strdup(argv[1])))
		return (del_list(head));
	head->status = CURSOR;
	while (argv[i])
	{
		if (strlen(argv[i]) != 0 && newlink(argv[i], head) == NULL)
			return (del_list(head));
		i++;
	}
	return (head);
}
