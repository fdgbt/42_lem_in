/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_rooms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:06:35 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/05 11:26:22 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_check_coord(int i, t_room *room, t_conf *conf)
{
	room->x = ft_atoim(conf->line + i++);
	if (conf->line[i] == '-' || conf->line[i] == '+')
		i++;
	while (conf->line[i] != ' ')
	{
		if (!conf->line[i] || conf->line[i] == '\n'
				|| !ft_isdigit(conf->line[i]))
			return (-12);
		i++;
	}
	room->y = ft_atoim(conf->line + i++);
	if (conf->line[i] == '-' || conf->line[i] == '+')
		i++;
	if (!conf->line[i] || conf->line[i] == '\n')
		return (-12);
	while (conf->line[i] && conf->line[i] != '\n')
	{
		if (!ft_isdigit(conf->line[i]))
			return (-12);
		i++;
	}
	if (room->x < INT_MIN || room->x > INT_MAX
			|| room->y < INT_MIN || room->y > INT_MAX)
		return (-17);
	return (0);
}

static t_room	*ft_check_dupli(t_room *temp, char *name)
{
	if (!ft_strcmp(name, temp->name))
		return (NULL);
	while (temp->next != NULL)
	{
		temp = temp->next;
		if (!ft_strcmp(name, temp->name))
			return (NULL);
	}
	return (temp);
}

static void		ft_init_room(t_room *temp, char *name, t_conf *conf)
{
	ft_strcpy(temp->name, name);
	temp->x = 0;
	temp->y = 0;
	temp->id = conf->nb_room++;
	temp->bfs_check = 0;
	temp->bfs_weight = 0;
	temp->bfs_backed = 0;
	temp->booked = 0;
	temp->used = 0;
	temp->ants = 0;
	temp->father = NULL;
	temp->father_sp = NULL;
	temp->next = NULL;
}

static int		ft_add_room(int i, t_room *temp, t_conf *conf)
{
	char	name[32];

	ft_bzero(name, 32);
	ft_strncpy(name, conf->line, i);
	if (!temp)
	{
		if (!(temp = (t_room *)malloc(sizeof(*temp))))
			return (-3);
		conf->first_room = temp;
	}
	else
	{
		if (!(temp = ft_check_dupli(temp, name)))
			return (-13);
		if (!(temp->next = (t_room *)malloc(sizeof(*temp))))
			return (-3);
		temp = temp->next;
	}
	ft_init_room(temp, name, conf);
	if (!conf->start && conf->next_start)
		conf->start = temp;
	if (!conf->end && conf->next_end)
		conf->end = temp;
	conf->last_room = temp;
	return (0);
}

int				ft_check_rooms(int i, int ret, t_conf *conf)
{
	while (1)
	{
		if ((ret = ft_check_comments(conf)) < 0 && ret == -7)
			return (-9);
		else if (ret < 0)
			return (ret);
		if (!ret)
			return (-4);
		i = 0;
		while (conf->line[i] != ' ')
		{
			if (!conf->line[i] || conf->line[i] == '\n')
				return (-11);
			if (i && conf->line[i] == '-')
				return (0);
			i++;
		}
		if (!i || i > 31)
			return (-16);
		if ((ret = ft_add_room(i, conf->first_room, conf)) < 0)
			return (ret);
		if ((ret = ft_check_coord(i, conf->last_room, conf)) < 0)
			return (ret);
	}
}
