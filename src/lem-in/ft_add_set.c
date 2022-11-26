/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:11:08 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 18:51:46 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_init_set(int i, t_set *set, t_conf *conf)
{
	set->best_laps = 0;
	set->first_path = NULL;
	set->first_path_sp = NULL;
	if (!(set->father_tab = (t_room **)malloc(sizeof(t_room *)
					* conf->nb_room)))
		return (-3);
	while (i < conf->nb_room)
		set->father_tab[i++] = NULL;
	set->next = NULL;
	conf->last_set = set;
	conf->max_flow = 0;
	return (0);
}

static int		ft_create_set(t_set *set, t_conf *conf)
{
	if (!set)
	{
		if (!(set = (t_set *)malloc(sizeof(*set))))
			return (-3);
		conf->first_set = set;
	}
	else
	{
		while (set->next)
			set = set->next;
		if (!(set->next = (t_set *)malloc(sizeof(*set))))
			return (-3);
		set = set->next;
	}
	if (ft_init_set(0, set, conf) < 0)
		return (-3);
	return (0);
}

static void		ft_reset_booking(int ret, t_conf *conf)
{
	t_room *room;

	if (!ret)
	{
		room = conf->first_room;
		while (room)
		{
			room->booked = 0;
			room = room->next;
		}
	}
}

static void		ft_reset_res_matrix(int i, int j, int ret, t_conf *conf)
{
	if (!ret)
	{
		while (i < conf->nb_room)
		{
			j = 0;
			while (j < conf->nb_room)
			{
				if (conf->adj_mat[i][j] && conf->res_mat[i][j] != 2)
					conf->res_mat[i][j] = 1;
				else if (conf->adj_mat[i][j])
				{
					if (conf->opt[10] && i < j)
						ft_print_graph(i, j, 0, conf);
					conf->adj_mat[i][j] = 0;
					conf->res_mat[i][j] = 0;
				}
				else
					conf->res_mat[i][j] = 0;
				j++;
			}
			i++;
		}
	}
}

int				ft_add_set(int ret, int cycle, t_conf *conf)
{
	if (ft_create_set(conf->first_set, conf) < 0)
		return (-3);
	while (conf->nb_path < conf->max_path && !ret)
	{
		if ((ret = ft_bfs(conf)) < 0)
			return (ret);
		if (conf->opt[4])
			ft_printf("# {GRE}BFS cycle:%d, ret:%d{OFF}\n", cycle, ret);
		if (!ret && (ret = ft_add_path(conf->last_set->first_path,
						NULL, conf)) < 0)
			return (-3);
		if (conf->opt[4] && !ret)
			ft_printf("ret:%d\n", ret);
		else if (conf->opt[4])
			ft_printf("# Add path, ret:%d\n", ret);
		cycle++;
	}
	ret = ft_pathfinder_sp(conf);
	if (conf->opt[3])
		ft_print_paths(conf);
	ft_reset_booking(ret, conf);
	ft_reset_res_matrix(0, 0, ret, conf);
	return (ret);
}
