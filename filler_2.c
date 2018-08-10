/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 18:44:34 by opokusyn          #+#    #+#             */
/*   Updated: 2018/05/08 18:44:36 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		wtf(t_filler *f, int y, int x)
{
	int		min;
	int		k;
	int		m;
	int		dist;

	min = 999999999;
	k = 0;
	while (k < f->p_y)
	{
		m = 0;
		while (m < f->p_x)
		{
			dist = manhattan_distance(f->i + k, f->j + m, y, x);
			if (f->piece[k][m] == '*' && dist < min)
				min = dist;
			m++;
		}
		k++;
	}
	return (min);
}

void	distance(t_filler *f)
{
	int		min_cur;
	int		min;
	int		x;
	int		y;

	min = 9999999;
	y = 0;
	while (y < f->map_y)
	{
		x = 0;
		while (x < f->map_x)
		{
			if (f->map[y][x] == f->en_pl)
			{
				if ((min_cur = wtf(f, y, x)) < min)
					min = min_cur;
			}
			x++;
		}
		y++;
	}
	f->possible_places[f->i][f->j] = min;
}

void	saving_place(t_filler *f, t_min *m)
{
	m->cur_min = f->possible_places[m->row][m->col];
	m->cur_min_x = m->row;
	m->cur_min_y = m->col;
}

void	min_iteration(t_filler *f)
{
	t_min	*m;

	m = malloc(sizeof(t_min));
	ft_init_min(m);
	while (m->row < f->map_y)
	{
		m->col = 0;
		while (m->col < f->map_x)
		{
			if (f->possible_places[m->row][m->col] > 0)
			{
				if (f->possible_places[m->row][m->col] < m->cur_min)
					saving_place(f, m);
			}
			m->col++;
		}
		m->row++;
	}
	f->x = m->cur_min_x;
	f->y = m->cur_min_y;
	ft_memdel((void **)&m);
}

void	last_place(t_filler *f)
{
	f->i = 0;
	while (f->i < f->map_y)
	{
		f->j = 0;
		while (f->j < f->map_x)
		{
			if (f->possible_places[f->i][f->j] == 1)
			{
				distance(f);
			}
			f->j++;
		}
		f->i++;
	}
	min_iteration(f);
}
