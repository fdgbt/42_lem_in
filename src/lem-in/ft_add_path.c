/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:12:15 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 18:52:36 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_print_path_data(t_path *path, t_conf *conf)
{
	float floor;
	float decim;

	floor = (int)conf->last_set->best_laps;
	decim = (conf->last_set->best_laps - floor) * 1000;
	ft_printf("# Add path, ants:%d nb_room:%d max_path:%d nb_path:%2d ",
			conf->ants, conf->nb_room, conf->max_path, conf->nb_path,
			conf->min_flow);
	ft_printf("min_flow:%d max_flow:%3d best_laps:%3d.%-3d ", conf->min_flow,
			conf->max_flow, (int)floor, (int)decim);
	floor = (int)path->laps;
	decim = (path->laps - floor) * 1000;
	ft_printf("path->id:%2d path->flow:%3d path->laps:%3d.%-3d ", path->id,
			path->flow, (int)floor, (int)decim);
}

static void		ft_update_res_mat(t_room *room, t_conf *conf)
{
	while (room->father)
	{
		room->father->booked = conf->nb_path;
		conf->res_mat[room->id][room->father->id] = -1;
		conf->res_mat[room->father->id][room->id] = 0;
		conf->last_set->father_tab[room->id] = room->father;
		room = room->father;
	}
}

static int		ft_update_path(t_path *path, t_room *room, t_conf *conf)
{
	while (room->father)
	{
		path->flow++;
		room = room->father;
	}
	if (path == conf->last_set->first_path)
		conf->min_flow = path->flow;
	conf->max_flow += path->flow;
	path->laps = (float)(conf->ants + conf->max_flow - conf->nb_path)
		/ (float)conf->nb_path;
	if (!conf->last_set->best_laps || conf->last_set->best_laps > path->laps)
		conf->last_set->best_laps = path->laps;
	else
	{
		conf->max_flow -= path->flow;
		conf->nb_path--;
		return (1);
	}
	ft_update_res_mat(conf->end, conf);
	if (conf->opt[4])
		ft_print_path_data(path, conf);
	return (0);
}

static void		ft_init_path(t_path *path, t_conf *conf)
{
	path->id = conf->nb_path;
	path->flow = 0;
	path->max_ants = 0;
	path->laps = 0;
	path->last_room = conf->end->father;
	path->next = NULL;
}

int				ft_add_path(t_path *path, t_path *last, t_conf *conf)
{
	conf->nb_path = 1;
	if (!path)
	{
		if (!(path = (t_path *)malloc(sizeof(*path))))
			return (-3);
		conf->last_set->first_path = path;
		last = path;
	}
	else
	{
		while (conf->nb_path++ && path->next)
			path = path->next;
		if (!(path->next = (t_path *)malloc(sizeof(*path))))
			return (-3);
		last = path;
		path = path->next;
	}
	ft_init_path(path, conf);
	if (ft_update_path(path, conf->end, conf) == 1)
	{
		free(path);
		last->next = NULL;
		return (1);
	}
	return (0);
}
