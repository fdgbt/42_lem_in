/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_best_laps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:20:45 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 20:56:27 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_print_input(int i, char *line, t_conf *conf)
{
	if (!conf->opt[0] || !line)
		ft_printf("%s\n", line);
	else if (line[0] == '#')
	{
		if (line[1] == '#')
			ft_printf("{YEL}%s{OFF}\n", line);
		else
			ft_printf("{GRE}%s{OFF}\n", line);
	}
	else if (ft_str_is_numeric(line))
		ft_printf("{BLU}%s{OFF}\n", line);
	else
	{
		while (line[i] && line[i] != ' ' && line[i] != '-')
			i++;
		if (line[i] == ' ')
			ft_printf("{CYA}%s{OFF}\n", line);
		else if (line[i] == '-')
			ft_printf("{MAG}%s{OFF}\n", line);
		else
			ft_printf("{WHI}%s{OFF}\n", line);
	}
}

static void		ft_del_input(t_conf *conf)
{
	t_input		*temp;
	t_input		*next;

	temp = conf->first_line;
	next = NULL;
	while (temp)
	{
		next = temp->next;
		ft_print_input(0, temp->line, conf);
		free(temp->line);
		free(temp);
		temp = next;
	}
	conf->first_line = NULL;
	conf->last_line = NULL;
}

static void		ft_select_path(t_set *set, t_path *path, t_conf *conf)
{
	while (path->laps != conf->best_laps)
	{
		path->max_ants = ft_ceil(set->best_laps) + 1 - path->flow;
		if (conf->opt[4])
			ft_printf("# {YEL}path->max_ants:%d{OFF}\n", path->max_ants);
		path = path->next;
	}
	path->max_ants = ft_ceil(set->best_laps) + 1 - path->flow;
	if (conf->opt[4])
		ft_printf("# {YEL}path->max_ants:%d{OFF}\n\n", path->max_ants);
	path = path->next;
	while (path)
	{
		path->flow = 0;
		path = path->next;
	}
	ft_del_input(conf);
}

static void		ft_print_debug(t_set *set, t_conf *conf)
{
	float floor;
	float decim;

	floor = (int)set->best_laps;
	decim = (set->best_laps - floor) * 1000;
	ft_printf("# {YEL}Best_laps, set->best_laps:%d.%-3d ",
			(int)floor, (int)decim);
	floor = (int)conf->best_laps;
	decim = (conf->best_laps - floor) * 1000;
	ft_printf("conf->best_laps:%d.%-3d{OFF}\n", (int)floor, (int)decim);
}

void			ft_best_laps(t_set *set, t_conf *conf)
{
	set = conf->first_set;
	conf->best_laps = set->best_laps;
	while (set)
	{
		if (set->best_laps < conf->best_laps)
			conf->best_laps = set->best_laps;
		set = set->next;
	}
	set = conf->first_set;
	conf->last_set = set;
	while (set->best_laps != conf->best_laps)
	{
		if (conf->opt[4])
			ft_print_debug(set, conf);
		set = set->next;
		conf->last_set = set;
	}
	if (conf->opt[4])
		ft_print_debug(set, conf);
	ft_select_path(set, set->first_path, conf);
}
