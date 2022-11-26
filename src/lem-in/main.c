/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:02:58 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/05 13:44:42 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		ft_init_config(t_conf *conf)
{
	conf->ants = 0;
	conf->nb_room = 0;
	conf->next_start = 0;
	conf->next_end = 0;
	conf->max_path = -1;
	conf->nb_path = 0;
	conf->min_flow = 0;
	conf->max_flow = 0;
	conf->best_laps = 0;
	conf->line = NULL;
	conf->first_line = NULL;
	conf->last_line = NULL;
	conf->first_bfs = NULL;
	conf->last_bfs = NULL;
	conf->first_set = NULL;
	conf->last_set = NULL;
	conf->first_room = NULL;
	conf->last_room = NULL;
	conf->start = NULL;
	conf->end = NULL;
	conf->link_a = NULL;
	conf->link_b = NULL;
	conf->adj_mat = NULL;
	conf->res_mat = NULL;
}

static int		ft_options(char *argv, const char *keys, t_conf *conf)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (keys[i])
	{
		if (argv[j] && argv[j] == keys[i])
		{
			if (!conf->opt[i])
				conf->opt[i] = 1;
			else
				return (-21);
			j++;
			if (!argv[j])
				return (0);
			i = -1;
		}
		i++;
	}
	return (-20);
}

static int		ft_check_options(int argc, char **argv, const char *keys,
		t_conf *conf)
{
	int i;
	int err;

	i = 0;
	err = 0;
	while (i < D_OPT_MAX)
		conf->opt[i++] = 0;
	if (argc > 1)
	{
		i = 1;
		while (argv[i])
		{
			if (argv[i][0] != '-' || !argv[i][1])
				return (-20);
			else if ((err = ft_options(argv[i], keys, conf)) < 0)
				return (err);
			i++;
		}
	}
	return (0);
}

static int		ft_print_man(t_conf *conf)
{
	int		fd;

	fd = 0;
	if ((fd = open(D_MAN_PATH, O_RDONLY)) < 0)
		return (-22);
	ft_printf("##VISUOFF\n");
	if (conf->opt[0])
		ft_printf("{GRE}%~{OFF}\n", fd);
	else
		ft_printf("%~\n", fd);
	if (close(fd) < 0)
		return (-22);
	return (0);
}

int				main(int argc, char **argv)
{
	t_conf				conf;
	int					err;
	static const char	keys[D_OPT_MAX] = {'c', 'e', 'l', 'p', 'd', 'b', 's',
		'f', 'i', 'h', 'v', 0};

	err = 0;
	ft_init_config(&conf);
	if ((err = ft_check_options(argc, argv, keys, &conf)) < 0)
		return (ft_end(err, &conf));
	if (conf.opt[9])
		return (ft_end(ft_print_man(&conf), &conf));
	if (conf.opt[0])
		ft_printf("##VISUOFF\n");
	if ((err = ft_check_file(&conf)) < 0)
		return (ft_end(err, &conf));
	if (!conf.start || !conf.end || conf.start == conf.end || conf.nb_room < 1)
		return (ft_end(-5, &conf));
	if (conf.opt[10] && (err = ft_print_graph(0, 0, 0, &conf)) < 0)
		return (ft_end(err, &conf));
	if ((err = ft_pathfinder(&conf)) < 0)
		return (ft_end(err, &conf));
	ft_print_laps(&conf);
	if (conf.opt[10] && (err = ft_print_graph(-1, -1, 0, &conf)) < 0)
		return (ft_end(err, &conf));
	return (ft_end(err, &conf));
}
