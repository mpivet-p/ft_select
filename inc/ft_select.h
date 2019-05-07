/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 13:58:25 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/05/05 23:09:26 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <curses.h>
# include <term.h>
# include <unistd.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <termios.h>
# include <fcntl.h>
# include <signal.h>

# define CURSOR 0xFF00
# define SELECTED 0xFF

typedef struct			s_select
{
	char				*name;
	int					status;
	struct	s_select	*next;
	struct	s_select	*prev;
}						t_select;

t_select				*remove_list(t_select *head);
void					list_select(t_select *ptr);
void					move_right(t_select *ptr);
void					move_left(t_select *ptr);
void					print_result(t_select *head);
t_select				*del_list(t_select *head);
t_select				*create_list(char **argv);
void					disp_list(t_select *ptr, int width);
int						term_init(void);
int						get_term_size(void);
int						init_keyboard(struct termios *init,
						struct termios *save);
void					sigwinch_handler(int signum);

#endif
