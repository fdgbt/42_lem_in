/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_links.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:07:04 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/05 11:22:22 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_room	*ft_find_room(int i, int j, t_room *temp, t_conf *conf)
{
	char		name[32];

	if (!temp)
		return (NULL);
	ft_bzero(name, 32);
	ft_strncpy(name, conf->line + i, j - i);
	while (temp != NULL)
	{
		if (!ft_strcmp(name, temp->name))
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static t_room	*ft_find_link(int i, int j, t_conf *conf)
{
	if (!i)
	{
		while (conf->line[j] != '-')
		{
			if (!conf->line[j] || conf->line[j] == '\n' || conf->line[j] == ' ')
				return (NULL);
			j++;
		}
	}
	else
	{
		while (conf->line[j])
		{
			if (conf->line[j] == '\n' || conf->line[j] == '-'
					|| conf->line[j] == ' ')
				return (NULL);
			j++;
		}
	}
	if (!(j - i) || (j - i) > 31)
		return (NULL);
	return (ft_find_room(i, j, conf->first_room, conf));
}

static int		ft_create_adj_matrix(int i, int j, t_conf *conf)
{
	if (!(conf->adj_mat = (t_room ***)malloc(sizeof(*conf->adj_mat)
					* conf->nb_room)))
		return (-3);
	while (i < conf->nb_room)
		conf->adj_mat[i++] = NULL;
	i = 0;
	while (i < conf->nb_room)
	{
		j = 0;
		if (!(conf->adj_mat[i] = (t_room **)malloc(sizeof(**conf->adj_mat)
						* conf->nb_room)))
			return (-3);
		while (j < conf->nb_room)
			conf->adj_mat[i][j++] = NULL;
		i++;
	}
	return (0);
}

static int		ft_add_link(int x, int y, t_conf *conf)
{
	x = conf->link_a->id;
	y = conf->link_b->id;
	if (!conf->adj_mat)
	{
		if (ft_create_adj_matrix(0, 0, conf) < 0)
			return (-3);
	}
	if (conf->adj_mat[x][y] || conf->adj_mat[y][x])
		return (-15);
	conf->adj_mat[x][y] = conf->link_b;
	conf->adj_mat[y][x] = conf->link_a;
	return (0);
}

int				ft_check_links(int i, int ret, int err, t_conf *conf)
{
	int		stop;

	stop = 0;
	while (ret)
	{
		i = 0;
		if (!(conf->link_a = ft_find_link(0, 0, conf)))
			return (ft_break(stop, -10));
		while (conf->line[i] != '-')
			i++;
		if (!(conf->link_b = ft_find_link(i + 1, i + 1, conf)))
			return (ft_break(stop, -10));
		if (conf->link_a == conf->link_b)
			return (ft_break(stop, -14));
		if ((err = ft_add_link(0, 0, conf)) < 0)
			return (ft_break(stop, err));
		if ((ret = ft_check_comments(conf)) < 0 && ret == -7)
			return (ft_break(stop, -10));
		else if (ret < 0)
			return (ft_break(stop, ret));
		if (!conf->opt[1])
			stop++;
	}
	return (0);
}
