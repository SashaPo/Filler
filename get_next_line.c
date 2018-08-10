/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:06:34 by opokusyn          #+#    #+#             */
/*   Updated: 2018/01/19 21:11:14 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		ft_fds_add(t_fds **afds, int fd)
{
	t_fds	*new;

	GNL_MCHECK((new = (t_fds *)malloc(sizeof(t_fds))));
	new->str = NULL;
	new->fd = fd;
	new->next = *afds;
	*afds = new;
	return (1);
}

static int		ft_parse_eof(t_fds *fds, char **line, int r)
{
	if (r == 0 && fds->str && *fds->str)
	{
		GNL_MCHECK((*line = ft_strsub(fds->str, 0, ft_strlen(fds->str) + 1)));
		ft_strdel(&fds->str);
		return (1);
	}
	else if (r == 0)
		return ((int)(*line = NULL));
	return (-1);
}

static int		ft_read_fd(t_fds *fds, char **line)
{
	char	*rem;
	char	*tmp;
	char	buf[GNL_BUFF_SIZE + 1];
	ssize_t	r;

	while (1)
	{
		if (fds->str && (rem = ft_strchr(fds->str, '\n')))
		{
			GNL_MCHECK((*line = ft_strsub(fds->str, 0, rem - fds->str)));
			tmp = ft_strsub(fds->str, (rem - fds->str) + 1, ft_strlen(rem) + 1);
			ft_strdel(&fds->str);
			return (tmp ? ((fds->str) = tmp) != NULL : -1);
		}
		else
		{
			if (!(r = read(fds->fd, buf, GNL_BUFF_SIZE)) || r == -1)
				return (ft_parse_eof(fds, line, r));
			buf[r] = '\0';
			GNL_MCHECK(tmp = ft_strjoin(fds->str ? fds->str : "", buf));
			ft_strdel(&fds->str);
			fds->str = tmp;
		}
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_fds	*fds = NULL;
	t_fds			*tmp;

	if (fd <= -1 || !line)
		return (-1);
	tmp = fds;
	while (tmp && tmp->fd != fd)
		tmp = tmp->next;
	if (!tmp)
	{
		if (ft_fds_add(&fds, fd) == -1)
			return (-1);
	}
	return (tmp ? ft_read_fd(tmp, line) : ft_read_fd(fds, line));
}
