/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:24:58 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 19:07:54 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_reset_used_room(t_conf *conf)
{
	t_room		*room;

	room = conf->first_room;
	while (room)
	{
		room->used = 0;
		room = room->next;
	}
}

static void		ft_print_room(int superpo, t_room *tmp_room, t_conf *conf)
{
	if (tmp_room == conf->start)
	{
		if (superpo)
			ft_printf("{BOLD}{GRE}[{CYA}%s{GRE}]{YEL} -> {OFF}",
					tmp_room->name);
		else
			ft_printf("{GRE}[{CYA}%s{GRE}]{YEL} -> {OFF}", tmp_room->name);
	}
	else if (!tmp_room->used)
	{
		if (superpo)
			ft_printf("{BOLD}{YEL}[{CYA}%s{YEL}] -> {OFF}", tmp_room->name);
		else
			ft_printf("{YEL}[{CYA}%s{YEL}] -> {OFF}", tmp_room->name);
	}
	else
	{
		if (superpo)
			ft_printf("{BOLD}{YEL}[{RED}%s{YEL}] -> {OFF}", tmp_room->name);
		else
			ft_printf("{YEL}[{RED}%s{YEL}] -> {OFF}", tmp_room->name);
	}
}

static void		ft_print_path(int superpo, t_room *tmp_room, t_conf *conf)
{
	if (tmp_room)
	{
		if (superpo)
			ft_print_path(superpo, tmp_room->father_sp, conf);
		else
			ft_print_path(superpo, tmp_room->father, conf);
		ft_print_room(superpo, tmp_room, conf);
		tmp_room->used++;
	}
}

static void		ft_print_set(int superpo, t_conf *conf)
{
	t_path		*tmp_path;

	tmp_path = conf->last_set->first_path;
	if (superpo)
		tmp_path = conf->last_set->first_path_sp;
	while (tmp_path)
	{
		ft_printf("\n# ");
		ft_print_path(superpo, tmp_path->last_room, conf);
		if (superpo)
			ft_printf("{BOLD}{RED}[{CYA}%s{RED}]{OFF}\n", conf->end->name);
		else
			ft_printf("{RED}[{CYA}%s{RED}]{OFF}\n", conf->end->name);
		tmp_path = tmp_path->next;
	}
}

void			ft_print_paths(t_conf *conf)
{
	ft_reset_used_room(conf);
	ft_print_set(0, conf);
	ft_print_set(1, conf);
	ft_printf("\n");
}
