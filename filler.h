/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opokusyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 10:46:33 by opokusyn          #+#    #+#             */
/*   Updated: 2018/04/15 10:46:35 by opokusyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H

# define FILLER_H

# define PLATEAU 7
# define PIECE 5

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include "get_next_line.h"

typedef struct		s_filler
{
	int				**possible_places;
	char			en_pl;
	char			my_pl;
	char			**piece;
	char			**map;
	char			map_x;
	char			map_y;
	char			p_x;
	char			p_y;
	int				x;
	int				y;
	int				i;
	int				j;
}					t_filler;

typedef struct		s_min
{
	int				cur_min;
	int				cur_min_x;
	int				cur_min_y;
	int				row;
	int				col;
}					t_min;

void				read_map(t_filler *f);
void				coordinates(t_filler *f);
void				last_place(t_filler *f);
void				read_piece(t_filler *f, char *line);
t_bool				can_place(t_filler *f, int y, int x);
void				distance(t_filler *f);
void				min_iteration(t_filler *f);
t_filler			ft_init(t_filler *f);
t_min				ft_init_min(t_min *m);
void				optimization(t_filler *f, int x, int y, int min_cur);
int					manhattan_distance(int x1, int y1, int x2, int y2);
void				ft_filler(t_filler *f, char *line);
void				ft_free_maps(t_filler *f);

#endif
