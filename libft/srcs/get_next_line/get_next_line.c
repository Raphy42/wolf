/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdantzer <rdantzer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 13:15:36 by fabientipper      #+#    #+#             */
/*   Updated: 2015/05/11 16:03:34 by rdantzer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_stock(char **save, char **buff, int fd)
{
	char		*tmp;
	int			buf;

	buf = 1;
	while (ft_strchr(*save, '\n') == NULL && buf > 0)
	{
		buf = read(fd, *buff, BUFF_SIZE);
		tmp = ft_strjoin(*save, *buff);
		free(*save);
		*save = tmp;
		ft_strclr(*buff);
	}
	return (buf);
}

int				ft_save(char **s, char **b, char **l, int buf)
{
	char		*tmp;
	char		*p;

	if (buf == -1)
	{
		free (*b);
		return (-1);
	}
	if (!(p = ft_strchr(*s, '\n')))
	{
		*l = ft_strdup(*s);
		free(*b);
		ft_strdel(s);
		return (0);
	}
	*p = '\0';
	*l = ft_strdup(*s);
	tmp = ft_strdup(*s + ft_strlen(*s) + 1);
	free(*s);
	*s = tmp;
	free(*b);
	return (1);
}

int				get_next_line(int const fd, char **line)
{
	static char	*save;
	char		*buff;

	if (fd == -1)
		return (-1);
	if ((save == NULL && !(save = ft_strnew(1))) ||
		!(buff = ft_strnew(BUFF_SIZE + 1)))
		return (-1);
	if (BUFF_SIZE > 0 && line)
		return (ft_save(&save, &buff, line, ft_stock(&save, &buff, fd)));
	return (-1);
}
