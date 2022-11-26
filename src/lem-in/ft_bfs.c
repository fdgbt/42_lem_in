/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:12:59 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 18:59:41 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_print_bfs(t_bfs *bfs, t_bfs *tmp, t_conf *conf)
{
	if (conf->opt[5])
		ft_printf("# {LIGHT}room added to bfs, name:%s father:%s{OFF}\n",
				bfs->room->name, bfs->room->father);
	if (conf->opt[7])
	{
		while (tmp)
		{
			ft_printf("# {LIGHT}{YEL}BFS FIFO, name:%s{OFF}\n",
					tmp->room->name);
			tmp = tmp->next;
		}
	}
}

static int		ft_add_bfs(t_room *new, t_bfs *bfs, t_conf *conf)
{
	if (!bfs)
	{
		if (!(bfs = (t_bfs *)malloc(sizeof(*bfs))))
			return (-3);
		conf->first_bfs = bfs;
	}
	else
	{
		if (!(bfs->next = (t_bfs *)malloc(sizeof(*bfs))))
			return (-3);
		bfs = bfs->next;
	}
	bfs->room = new;
	bfs->next = NULL;
	new->bfs_check++;
	conf->last_bfs = bfs;
	if (conf->opt[5] || conf->opt[7])
		ft_print_bfs(bfs, conf->first_bfs, conf);
	return (0);
}

static int		ft_find_connect(int i, int j, t_conf *conf)
{
	i = conf->first_bfs->room->id;
	j = 0;
	while (j < conf->nb_room && !conf->end->bfs_check)
	{
		if (conf->res_mat[i][j] == 1 && !conf->adj_mat[i][j]->bfs_check)
		{
			if (conf->opt[5])
				ft_printf("# {LIGHT}{BLU}BFS, classic, room:%s id:%d{OFF}\n",
						conf->first_bfs->room->name, conf->first_bfs->room->id);
			if (!conf->adj_mat[i][j]->booked)
			{
				conf->adj_mat[i][j]->father = conf->first_bfs->room;
				if (ft_add_bfs(conf->adj_mat[i][j],
							conf->last_bfs, conf) < 0)
					return (-3);
			}
		}
		j++;
	}
	return (ft_bfs_reset(0, 0, conf->first_room, conf));
}

int				ft_bfs(t_conf *conf)
{
	if (ft_add_bfs(conf->start, conf->last_bfs, conf) < 0)
		return (ft_bfs_reset(1, -3, conf->first_room, conf));
	while (conf->first_bfs && !conf->end->bfs_check)
	{
		if (ft_find_connect(0, 0, conf) < 0)
			return (ft_bfs_reset(1, -3, conf->first_room, conf));
	}
	if (!conf->end->bfs_check)
		return (ft_bfs_reset(1, 1, conf->first_room, conf));
	return (ft_bfs_reset(1, 0, conf->first_room, conf));
}
