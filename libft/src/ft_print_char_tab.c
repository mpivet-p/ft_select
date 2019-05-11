/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 12:43:39 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/01/05 12:58:58 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_char_tab(char **tab)
{
	int		i;
	char	*result;
	char	*tmp;

	i = 1;
	tmp = NULL;
	result = ft_strjoin(tab[0], "\n");
	while (tab[i])
	{
		tmp = ft_strjoin(result, tab[i]);
		ft_strdel(&result);
		result = tmp;
		tmp = ft_strjoin(result, "\n");
		ft_strdel(&result);
		result = tmp;
		i++;
	}
	ft_putstr(result);
	ft_strdel(&result);
}
