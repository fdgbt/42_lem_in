/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:05:21 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/05 11:20:39 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_check_ants(int ret, t_conf *conf)
{
	if ((ret = ft_check_comments(conf)) < 0)
	{
		if (ret == -7)
			return (-6);
		return (ret);
	}
	if (!ret)
		return (-4);
	if (!ft_str_is_numeric(conf->line))
		return (-6);
	conf->ants = ft_atoim(conf->line);
	if (conf->ants <= 0)
		return (-18);
	if (conf->ants > INT_MAX)
		return (-19);
	return (0);
}

static int		ft_free_line(int error, t_conf *conf)
{
	if (error)
		ft_get_next_line(0, NULL);
	if (!error || error == -4 || error == -8 || error == -30)
	{
		if (conf->line)
			free(conf->line);
		conf->line = NULL;
	}
	return (error);
}

int				ft_check_file(t_conf *conf)
{
	int		err;

	err = 0;
	if ((err = ft_check_ants(0, conf)) < 0)
		return (ft_free_line(err, conf));
	if ((err = ft_check_rooms(0, 0, conf)) < 0)
		return (ft_free_line(err, conf));
	if ((err = ft_check_links(0, 1, 0, conf)) < 0)
		return (ft_free_line(err, conf));
	return (ft_free_line(err, conf));
}
