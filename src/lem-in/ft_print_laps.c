/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_laps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:20:22 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 18:53:39 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_fill_path_one(t_conf *conf)
{
	ft_printf("\n");
	while (conf->end->ants < conf->ants)
	{
		conf->end->ants++;
		conf->start->ants--;
		ft_printf("L%d-%s ", conf->end->ants, conf->end->name);
	}
	ft_printf("\n");
	return (1);
}

static void		ft_move_ants(int laps, t_room *room, t_path *path, t_conf *conf)
{
	if (room == conf->start)
	{
		if (laps <= path->max_ants)
		{
			conf->last_room->ants = conf->ants - conf->start->ants + 1;
			ft_printf("L%d-%s ", conf->last_room->ants, conf->last_room->name);
			room->ants--;
		}
	}
	else
	{
		ft_printf("L%d-%s ", room->ants, conf->last_room->name);
		if (conf->last_room == conf->end)
			conf->last_room->ants++;
		else
			conf->last_room->ants = room->ants;
		room->ants = 0;
	}
}

static int		ft_fill_path(t_path *path, t_room *room, t_conf *conf)
{
	int		laps;

	laps = 0;
	ft_printf("\n");
	while (conf->end->ants < conf->ants)
	{
		laps++;
		while (path)
		{
			conf->last_room = conf->end;
			room = path->last_room;
			while (path->flow && room)
			{
				if (room->ants)
					ft_move_ants(laps, room, path, conf);
				conf->last_room = room;
				room = conf->last_set->father_tab[room->id];
			}
			path = path->next;
		}
		ft_printf("\n");
		path = conf->last_set->first_path;
	}
	return (laps);
}

void			ft_print_laps(t_conf *conf)
{
	int		laps;

	laps = 0;
	conf->start->ants = conf->ants;
	conf->end->ants = 0;
	ft_best_laps(conf->first_set, conf);
	if (conf->last_set->first_path->flow == 1)
		laps = ft_fill_path_one(conf);
	else
		laps = ft_fill_path(conf->last_set->first_path,
				conf->last_set->first_path->last_room, conf);
	if (conf->opt[2])
		ft_printf("\n# {YEL}Total laps:%d{OFF}\n", laps);
}
