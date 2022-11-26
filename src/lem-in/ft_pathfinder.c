/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathfinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:08:59 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 14:23:29 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_set_max_path(int i, int j, t_conf *conf)
{
	int		max_path;

	max_path = 0;
	while (j < conf->nb_room)
	{
		if (conf->adj_mat[i][j])
			max_path++;
		j++;
	}
	if (conf->max_path == -1 || conf->max_path > max_path)
		conf->max_path = max_path;
}

static int		ft_create_res_matrix(int i, int j, t_conf *conf)
{
	if (!(conf->res_mat = (int **)malloc(sizeof(*conf->res_mat)
					* conf->nb_room)))
		return (-3);
	while (i < conf->nb_room)
		conf->res_mat[i++] = 0;
	i = 0;
	while (i < conf->nb_room)
	{
		j = 0;
		if (!(conf->res_mat[i] = (int *)malloc(sizeof(**conf->res_mat)
						* conf->nb_room)))
			return (-3);
		while (j < conf->nb_room)
		{
			if (conf->adj_mat[i][j])
				conf->res_mat[i][j] = 1;
			else
				conf->res_mat[i][j] = 0;
			j++;
		}
		i++;
	}
	return (0);
}

int				ft_pathfinder(t_conf *conf)
{
	int		ret_sp;

	ret_sp = 0;
	ft_set_max_path(conf->start->id, 0, conf);
	ft_set_max_path(conf->end->id, 0, conf);
	if (!conf->max_path)
		return (-1);
	if (ft_create_res_matrix(0, 0, conf) < 0)
		return (-3);
	while (conf->nb_path < conf->max_path && !ret_sp)
		ret_sp = ft_add_set(0, 1, conf);
	if (!conf->first_set->first_path && !conf->first_set->first_path_sp)
		return (-1);
	if (ret_sp < 0)
		return (ret_sp);
	return (0);
}
