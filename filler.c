/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 10:45:43 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/15 10:45:45 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_filler	ft_init(t_filler *f)
{
	f->possible_places = malloc(sizeof(char **));
	f->map = malloc(sizeof(char **));
	f->piece = malloc(sizeof(char **));
	f->my_pl = 0;
	f->en_pl = 0;
	f->map_y = 0;
	f->map_x = 0;
	f->p_y = 0;
	f->p_x = 0;
	f->y = 0;
	f->x = 0;
	return (*f);
}

void		read_map(t_filler *f)
{
	int		map_size;
	int		i;
	char	*line;

	i = 0;
	map_size = 0;
	line = NULL;
	f->map = (char **)malloc(sizeof(char *) * f->map_y);
	get_next_line(0, &line);
	ft_memdel((void **)&line);
	while (i < f->map_y)
	{
		get_next_line(0, &line);
		f->map[i++] = ft_strdup(line + 4);
		ft_memdel((void **)&line);
	}
}

void		read_piece(t_filler *f, char *line)
{
	int		piece_size;
	int		i;
	char	*piece_line;

	i = 0;
	piece_line = NULL;
	f->p_y = ft_atoi(line + PIECE);
	f->p_x = ft_atoi(ft_strchr(line + PIECE + 1, ' '));
	ft_memdel((void **)&line);
	piece_size = f->p_y;
	f->piece = (char **)malloc(sizeof(char *) * piece_size);
	i = 0;
	while (i < f->p_y)
	{
		get_next_line(0, &piece_line);
		f->piece[i] = ft_strdup(piece_line);
		ft_memdel((void **)&piece_line);
		i++;
	}
}

void		coordinates(t_filler *f)
{
	int		i;
	int		j;

	i = 0;
	f->possible_places = (int **)malloc(sizeof(int *) * f->map_y);
	while (i < f->map_y)
	{
		j = 0;
		f->possible_places[i] = (int *)malloc(sizeof(int) * (f->map_x + 1));
		while (j < f->map_x)
		{
			if (can_place(f, i, j))
				f->possible_places[i][j] = 1;
			else
				f->possible_places[i][j] = 0;
			j++;
		}
		i++;
	}
	last_place(f);
}

t_bool		can_place(t_filler *f, int y, int x)
{
	int		i;
	int		j;
	int		cnt;

	i = 0;
	cnt = 0;
	while (i < f->p_y)
	{
		j = 0;
		while (j < f->p_x)
		{
			if (((y + i) >= f->map_y || (x + j) >= f->map_x))
				return (FALSE);
			else if (f->piece[i][j] == '*' && f->map[y + i][x + j] == f->en_pl)
				return (FALSE);
			else if (f->piece[i][j] == '*' && f->map[y + i][x + j] == f->my_pl)
				cnt++;
			j++;
		}
		i++;
	}
	return (cnt == 1);
}
