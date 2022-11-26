/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:04:43 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 14:22:50 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_del_matrix(t_conf *conf)
{
	int		i;

	if (conf->adj_mat)
	{
		i = 0;
		while (i < conf->nb_room)
			free(conf->adj_mat[i++]);
		free(conf->adj_mat);
		conf->adj_mat = NULL;
	}
	if (conf->res_mat)
	{
		i = 0;
		while (i < conf->nb_room)
			free(conf->res_mat[i++]);
		free(conf->res_mat);
		conf->res_mat = NULL;
	}
}

static void		ft_del_path(t_path *path)
{
	t_path		*p_next;

	p_next = NULL;
	while (path)
	{
		p_next = path->next;
		free(path);
		path = p_next;
	}
}

static void		ft_del_set(t_conf *conf)
{
	t_set		*set;
	t_set		*s_next;

	set = conf->first_set;
	s_next = NULL;
	while (set)
	{
		free(set->father_tab);
		ft_del_path(set->first_path);
		ft_del_path(set->first_path_sp);
		s_next = set->next;
		free(set);
		set = s_next;
	}
	conf->first_set = NULL;
}

static void		ft_del_rooms(t_conf *conf)
{
	t_room		*temp;
	t_room		*next;

	temp = conf->first_room;
	next = NULL;
	while (temp)
	{
		next = temp->next;
		free(temp);
		temp = next;
	}
	conf->first_room = NULL;
}

void			ft_clean(t_conf *conf)
{
	t_input		*temp;
	t_input		*next;

	temp = conf->first_line;
	next = NULL;
	while (temp)
	{
		next = temp->next;
		if (temp->line)
			free(temp->line);
		free(temp);
		temp = next;
	}
	ft_del_set(conf);
	ft_del_matrix(conf);
	ft_del_rooms(conf);
}
