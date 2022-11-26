/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_comments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 20:05:55 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/05 11:25:38 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		ft_check_command(t_conf *conf)
{
	static const char	commands[2][6] = {{"start"}, {"end"}};
	int					i;
	int					j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 6 && conf->line[j + 2] && commands[i][j]
				&& conf->line[j + 2] == commands[i][j])
		{
			j++;
			if (!conf->line[j + 2] && !commands[i][j])
			{
				if (!i && !conf->next_start)
					conf->next_start = 1;
				else if (i && !conf->next_end)
					conf->next_end = 1;
				else
					return (-1);
			}
		}
		i++;
	}
	return (0);
}

static int		ft_add_line(int ret, t_input *temp, t_conf *conf)
{
	if (!ret)
		return (0);
	if (!conf->line)
		return (-2);
	if (!temp)
	{
		if (!(temp = (t_input *)malloc(sizeof(*temp))))
			return (-30);
		conf->first_line = temp;
	}
	else
	{
		if (!(temp->next = (t_input *)malloc(sizeof(*temp))))
			return (-30);
		temp = temp->next;
	}
	temp->line = conf->line;
	temp->next = NULL;
	conf->last_line = temp;
	return (0);
}

int				ft_check_comments(t_conf *conf)
{
	int		ret;
	int		err;

	ret = 0;
	err = 0;
	if ((ret = ft_get_next_line(0, &conf->line)) < 0)
		return (-2);
	while (ret && conf->line && conf->line[0] == '#')
	{
		if (conf->line[1] == '#' && ft_check_command(conf) < 0)
			return (-8);
		if ((err = ft_add_line(ret, conf->last_line, conf)) < 0)
			return (err);
		if ((ret = ft_get_next_line(0, &conf->line)) < 0)
			return (-2);
	}
	if ((err = ft_add_line(ret, conf->last_line, conf)) < 0)
		return (err);
	if (ret && conf->line && (conf->line[0] == '\n' || conf->line[0] == '#'
				|| conf->line[0] == 'L' || conf->line[0] == ' '
				|| conf->line[0] == '-'))
		return (-7);
	return (ret);
}
