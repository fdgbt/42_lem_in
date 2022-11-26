/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathfinder_sp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:14:37 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 18:51:08 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_update_res_mat_sp(t_path *path, t_room *room, t_conf *conf)
{
	int		flow;

	flow = 0;
	while (room->father_sp)
	{
		if (conf->res_mat[room->id][room->father_sp->id] == 1)
		{
			conf->res_mat[room->id][room->father_sp->id] = -1;
			conf->res_mat[room->father_sp->id][room->id] = 0;
		}
		else
		{
			conf->res_mat[room->id][room->father_sp->id] = 2;
			conf->res_mat[room->father_sp->id][room->id] = 2;
		}
		room->father_sp->booked = path->id;
		room = room->father_sp;
		flow++;
	}
	if (conf->opt[4])
		ft_printf("# Add path SP, id:%d flow:%d\n", path->id, path->flow);
}

static int		ft_add_path_sp(t_path *path, t_conf *conf)
{
	if (!(path = (t_path *)malloc(sizeof(*path))))
		return (-3);
	conf->last_set->first_path_sp = path;
	path->last_room = conf->end->father_sp;
	path->id = -1;
	path->flow = 0;
	path->laps = 0;
	path->next = NULL;
	ft_update_res_mat_sp(path, conf->end, conf);
	return (0);
}

int				ft_pathfinder_sp(t_conf *conf)
{
	int			ret;

	ret = 0;
	if ((ret = ft_bfs_sp(conf)) < 0)
		return (ret);
	if (conf->opt[4])
		ft_printf("# {RED}BFS SP, ret:%d{OFF}\n", ret);
	if (!ret && (ft_add_path_sp(conf->last_set->first_path_sp, conf) < 0))
		return (-3);
	if (conf->opt[4] && !conf->opt[3])
		ft_printf("\n", ret);
	return (ret);
}
