/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bfs_reset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:32:43 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 14:23:50 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_bfs_rem(t_bfs *temp, t_conf *conf)
{
	free(conf->first_bfs);
	if (!temp)
	{
		conf->first_bfs = NULL;
		conf->last_bfs = NULL;
	}
	else
		conf->first_bfs = temp;
}

int				ft_bfs_reset(int all, int ret, t_room *room, t_conf *conf)
{
	t_bfs		*temp_bfs;
	t_bfs		*next;

	if (!all)
		ft_bfs_rem(conf->first_bfs->next, conf);
	else
	{
		temp_bfs = conf->first_bfs;
		next = NULL;
		while (room)
		{
			room->bfs_check = 0;
			room = room->next;
		}
		while (temp_bfs)
		{
			next = temp_bfs->next;
			free(temp_bfs);
			temp_bfs = next;
		}
		conf->first_bfs = NULL;
		conf->last_bfs = NULL;
	}
	return (ret);
}
