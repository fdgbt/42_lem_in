/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs_sp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:16:15 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 19:00:09 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_order_bfs(t_bfs *bfs, t_room *new, int weight, t_conf *conf)
{
	t_bfs		*tmp;
	t_bfs		*last;

	tmp = NULL;
	last = NULL;
	new->bfs_weight = new->father_sp->bfs_weight + weight;
	tmp = conf->first_bfs->next;
	while (tmp && tmp->room->bfs_weight <= new->bfs_weight)
	{
		last = tmp;
		tmp = tmp->next;
	}
	if (last)
		last->next = bfs;
	if (tmp == conf->first_bfs->next)
		conf->first_bfs->next = bfs;
	bfs->next = tmp;
}

static void		ft_print_bfs_sp(t_bfs *bfs, t_bfs *tmp, t_conf *conf)
{
	if (conf->opt[6])
	{
		ft_printf("# {ITAL}room added to bfs_sp, name:%s father_sp:%s ",
				bfs->room->name, bfs->room->father_sp);
		ft_printf("bfs_weight:%d bfs_backed:%d{OFF}\n",
				bfs->room->bfs_weight, bfs->room->bfs_backed);
	}
	if (conf->opt[8])
	{
		while (tmp)
		{
			ft_printf("# {ITAL}{YEL}BFS SP HEAP, name:%s bfs_weight:%d ",
					tmp->room->name, tmp->room->bfs_weight);
			ft_printf("bfs_backed:%d{OFF}\n", tmp->room->bfs_backed);
			tmp = tmp->next;
		}
	}
}

static int		ft_add_bfs_sp(t_bfs *bfs, t_room *new, int weight, t_conf *conf)
{
	if (new->father_sp && ((new->booked && new->father_sp->booked)
				|| new->father_sp->bfs_backed))
		new->bfs_backed = 1;
	if (!(bfs = (t_bfs *)malloc(sizeof(*bfs))))
		return (-3);
	bfs->room = new;
	bfs->next = NULL;
	new->bfs_check++;
	if (!conf->first_bfs)
		conf->first_bfs = bfs;
	else
		ft_order_bfs(bfs, new, weight, conf);
	if (conf->opt[6] || conf->opt[8])
		ft_print_bfs_sp(bfs, conf->first_bfs, conf);
	return (0);
}

static int		ft_find_connect_sp(int i, int j, t_bfs *first, t_conf *conf)
{
	i = first->room->id;
	j = 0;
	while (j < conf->nb_room && !conf->end->bfs_check && !conf->end->bfs_backed)
	{
		if (conf->res_mat[i][j] != 0 && !conf->adj_mat[i][j]->bfs_check)
		{
			if (conf->opt[6])
			{
				if (conf->res_mat[i][j] == -1)
					ft_printf("# {ITAL}{MAG}BFS SP, back, ");
				else
					ft_printf("# {ITAL}{CYA}BFS SP, classic, ");
				ft_printf("room:%s weight:%d id:%d{OFF}\n", first->room->name,
						first->room->bfs_weight, first->room->id);
			}
			conf->adj_mat[i][j]->father_sp = first->room;
			if (conf->adj_mat[i][j] != conf->end
					|| conf->adj_mat[i][j]->father_sp->bfs_backed)
				if (ft_add_bfs_sp(NULL, conf->adj_mat[i][j],
							conf->res_mat[i][j], conf) < 0)
					return (-3);
		}
		j++;
	}
	return (ft_bfs_reset(0, 0, conf->first_room, conf));
}

int				ft_bfs_sp(t_conf *conf)
{
	conf->start->booked = 0;
	conf->end->booked = 0;
	if (ft_add_bfs_sp(NULL, conf->start, 0, conf) < 0)
		return (ft_bfs_reset(1, -3, conf->first_room, conf));
	while (conf->first_bfs && !conf->end->bfs_backed)
	{
		while (conf->first_bfs && !conf->end->bfs_check)
		{
			if (ft_find_connect_sp(0, 0, conf->first_bfs, conf) < 0)
				return (ft_bfs_reset(1, -3, conf->first_room, conf));
		}
		if (!conf->end->bfs_backed)
			conf->end->bfs_check = 0;
	}
	if (!conf->end->bfs_check || !conf->end->bfs_check)
		return (ft_bfs_reset(1, 1, conf->first_room, conf));
	return (ft_bfs_reset(1, 0, conf->first_room, conf));
}
