/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:59:07 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/01/05 11:48:42 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strnjoin(char const *s1, char const *s2,
		int len, char **line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + len + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (j < len)
		str[i++] = s2[j++];
	str[i] = '\0';
	free(*line);
	return (str);
}

static t_list	*find_fd_in_list(t_list **ptr, const int fd)
{
	t_gnl	*tmp;
	t_gnl	*new;
	t_list	*newlink;
	t_list	*buf_list;

	buf_list = *ptr;
	while (buf_list->next != NULL)
	{
		tmp = buf_list->content;
		if (tmp->fd == fd)
			return (buf_list);
		else
			buf_list = buf_list->next;
	}
	if (!(newlink = (t_list*)ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (!(new = (t_gnl*)ft_memalloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = (const int)fd;
	new->ret = BUFF_SIZE;
	newlink->content = new;
	ft_lstadd(ptr, newlink);
	return (*ptr);
}

static int		read_line(t_gnl *buffer, char **line, int i)
{
	while (++i <= buffer->ret && buffer->buf[i] != 10 && buffer->ret > 0)
	{
		if (buffer->buf[i] == 0 && buffer->ret == BUFF_SIZE)
		{
			*line = ft_strnjoin(*line, buffer->buf, i, &(*line));
			ft_strclr(buffer->buf);
			if ((buffer->ret = read(buffer->fd, buffer->buf, BUFF_SIZE)) == -1)
				return (-1);
			buffer->buf[BUFF_SIZE] = 0;
			i = 0;
		}
	}
	if (ft_strchr(buffer->buf, '\n'))
	{
		*line = ft_strnjoin(*line, buffer->buf, i++, &(*line));
		ft_strncpy(buffer->buf, ft_strchr(buffer->buf, '\n') + 1, BUFF_SIZE);
	}
	else if (buffer->buf[0] != 0 || *line[0] != 0)
	{
		*line = ft_strnjoin(*line, buffer->buf, i++, &(*line));
		ft_strclr(buffer->buf);
	}
	else
		return (0);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*ptr;
	t_list			*link;
	t_gnl			*buffer;
	int				ret;

	ret = -1;
	if (fd < 0 || line == NULL)
		return (-1);
	if (!ptr)
		ptr = ft_lstnew(NULL, 0);
	if (!(link = find_fd_in_list(&ptr, fd)))
		return (-1);
	*line = ft_strnew(1);
	buffer = link->content;
	if (buffer->buf[0] == 0)
		buffer->ret = BUFF_SIZE;
	if ((ret = read_line(buffer, &(*line), -1)) == 0)
		ft_strdel(line);
	return (ret);
}
