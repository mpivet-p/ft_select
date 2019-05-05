/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 22:09:46 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/05 23:16:33 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

extern t_select	*global_head;

void	sigwinch_handler(int signum)
{
	(void)signum;
	signal(SIGWINCH, sigwinch_handler);
	disp_list(global_head, get_term_size() & 0xFFFF);
}
