/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_graph.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:29:12 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 14:24:09 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_print_links(int i, int j, int fd, t_conf *conf)
{
	while (i < conf->nb_room)
	{
		j = i + 1;
		while (j < conf->nb_room)
		{
			if (conf->adj_mat[i][j])
				ft_printf("%@\t%s -- %s;\n", fd, conf->adj_mat[i][j]->name,
						conf->adj_mat[j][i]->name);
			j++;
		}
		i++;
	}
}

static void		ft_print_pos(t_room *room, int fd)
{
	if (room->x < 0)
		room->x = -(room->x);
	if (room->y < 0)
		room->y = -(room->y);
	ft_printf("%@\tpos = \"%d,%d!\"\n", fd, room->x, room->y);
}

static void		ft_print_rooms(t_room *room, int fd, t_conf *conf)
{
	static const char	color[30][15] = {{0}, {"cadetblue"}, {"khaki"},
		{"cyan"}, {"yellow"}, {"magenta"}, {"orange"}, {"pink"}, {"sienna"},
		{"purple"}, {"darkgreen"}, {"red4"}, {"dodgerblue"}, {"olivedrab"},
		{"turquoise"}, {"goldenrod"}, {"orchid"}, {"orangered"}, {"deeppink"},
		{"peru"}, {"indigo"}, {"salmon"}, {"tomato"}, {"coral"}, {"khaki4"},
		{"peachpuff"}, {0}};

	while (room)
	{
		ft_printf("%@\n%s [\n", fd, room->name);
		ft_print_pos(room, fd);
		if (room == conf->start)
			ft_printf("%@\tstyle = filled fillcolor = \"green\"\n", fd);
		else if (room == conf->end)
			ft_printf("%@\tstyle = filled fillcolor = \"red\"\n", fd);
		else if (room->booked && room->booked <= 25)
			ft_printf("%@\tstyle = filled fillcolor = \"%s\"\n", fd,
					color[room->booked]);
		else if (room->booked)
			ft_printf("%@\tstyle = filled fillcolor = \"blue\"\n", fd);
		ft_printf("%@]\n", fd);
		room = room->next;
	}
	ft_printf("%@}\n", fd);
}

int				ft_print_graph(int i, int j, int fd, t_conf *conf)
{
	if (!i && !j)
	{
		if (!(fd = open(D_DOT_PATH, O_RDWR | O_TRUNC | O_CREAT, S_IRWXU)))
			return (-23);
		else
			ft_printf("%@graph lem_in {\nsplines=ortho\noverlap=false\n", fd);
	}
	else
	{
		if (!(fd = open(D_DOT_PATH, O_RDWR | O_APPEND, S_IRWXU)))
			return (-23);
		else if (i > 0 && j > 0)
			ft_printf("%@\t%s -- %s [color = red];\n", fd,
					conf->adj_mat[i][j]->name, conf->adj_mat[j][i]->name);
		else
		{
			ft_print_links(0, 0, fd, conf);
			ft_print_rooms(conf->first_room, fd, conf);
		}
	}
	if (fd && close(fd) < 0)
		return (-23);
	return (0);
}
