/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <opokusyn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:11:02 by opokusyn          #+#    #+#             */
/*   Updated: 2018/01/19 21:11:16 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

#define ABS(x) ((x) >= 0 ? (x) : -(x))

int		main(void)
{
	t_filler	*f;
	char		*line;
	int			i;

	i = 0;
	line = NULL;
	f = malloc(sizeof(t_filler));
	ft_init(f);
	if (!get_next_line(0, &line))
		return (1);
	if (!ft_strstr(line, "p1") && !ft_strstr(line, "p2"))
		return (1);
	f->my_pl = (ft_strstr(line, "p1")) ? 'O' : 'X';
	f->en_pl = (f->my_pl == 'O') ? 'X' : 'O';
	ft_filler(f, line);
	ft_memdel((void **)&f);
	return (0);
}

int		manhattan_distance(int x1, int y1, int x2, int y2)
{
	return (ABS(x2 - x1) + ABS(y2 - y1));
}

void	ft_filler(t_filler *f, char *line)
{
	while (1)
	{
		if (get_next_line(0, &line) < 1 || !ft_strstr(line, "Plateau "))
			break ;
		f->map_y = ft_atoi(&(line[PLATEAU]));
		f->map_x = ft_atoi(ft_strchr(&(line[PLATEAU + 1]), ' '));
		ft_memdel((void **)&line);
		read_map(f);
		if (!get_next_line(0, &line))
			break ;
		read_piece(f, line);
		coordinates(f);
		ft_putnbr(f->x);
		write(1, " ", 1);
		ft_putnbr(f->y);
		write(1, "\n", 1);
		ft_free_maps(f);
	}
}

void	ft_free_maps(t_filler *f)
{
	int			i;

	i = 0;
	while (i < f->map_y)
	{
		ft_memdel((void **)&f->map[i]);
		ft_memdel((void **)&f->possible_places[i]);
		i++;
	}
	ft_memdel((void **)&f->map);
	ft_memdel((void **)&f->possible_places);
	i = 0;
	while (i < f->p_y)
	{
		ft_memdel((void **)&f->piece[i]);
		i++;
	}
	ft_memdel((void **)&f->piece);
}

t_min	ft_init_min(t_min *m)
{
	m->cur_min = 999999999;
	m->cur_min_x = 0;
	m->cur_min_y = 0;
	m->row = 0;
	m->col = 0;
	return (*m);
}
