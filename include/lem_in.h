/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdagbert <fdagbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:48:51 by fdagbert          #+#    #+#             */
/*   Updated: 2019/07/04 14:22:22 by fdagbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define D_OPT_MAX 12
# define D_MAN_PATH "./src/man/man_lem"
# define D_DOT_PATH "./lem.dot"

# include "ft_printf.h"

typedef struct		s_input
{
	char			*line;
	struct s_input	*next;
}					t_input;

typedef struct		s_room
{
	char			name[32];
	intmax_t		x;
	intmax_t		y;
	int				id;
	int				bfs_check;
	int				bfs_weight;
	int				bfs_backed;
	int				booked;
	int				used;
	int				ants;
	struct s_room	*father;
	struct s_room	*father_sp;
	struct s_room	*next;
}					t_room;

typedef struct		s_bfs
{
	t_room			*room;
	struct s_bfs	*next;
}					t_bfs;

typedef struct		s_path
{
	int				id;
	int				flow;
	int				max_ants;
	float			laps;
	t_room			*last_room;
	struct s_path	*next;
}					t_path;

typedef struct		s_set
{
	float			best_laps;
	t_path			*first_path;
	t_path			*first_path_sp;
	t_room			**father_tab;
	struct s_set	*next;
}					t_set;

typedef struct		s_conf
{
	intmax_t		ants;
	int				opt[11];
	int				nb_room;
	int				next_start;
	int				next_end;
	int				max_path;
	int				nb_path;
	int				min_flow;
	int				max_flow;
	float			best_laps;
	char			*line;
	t_input			*first_line;
	t_input			*last_line;
	t_bfs			*first_bfs;
	t_bfs			*last_bfs;
	t_set			*first_set;
	t_set			*last_set;
	t_room			*first_room;
	t_room			*last_room;
	t_room			*start;
	t_room			*end;
	t_room			*link_a;
	t_room			*link_b;
	t_room			***adj_mat;
	int				**res_mat;
}					t_conf;

int					ft_check_file(t_conf *conf);
int					ft_check_comments(t_conf *conf);
int					ft_check_rooms(int i, int ret, t_conf *conf);
int					ft_check_links(int i, int ret, int err, t_conf *conf);
int					ft_pathfinder(t_conf *conf);
int					ft_pathfinder_sp(t_conf *conf);
int					ft_add_set(int ret, int cycle, t_conf *conf);
int					ft_add_path(t_path *path, t_path *last, t_conf *conf);
int					ft_bfs(t_conf *conf);
int					ft_bfs_sp(t_conf *conf);
int					ft_bfs_reset(int all, int ret, t_room *room, t_conf *conf);
int					ft_end(int error, t_conf *conf);
int					ft_print_graph(int i, int j, int fd, t_conf *conf);
void				ft_clean(t_conf *conf);
void				ft_print_paths(t_conf *conf);
void				ft_print_laps(t_conf *conf);
void				ft_best_laps(t_set *set, t_conf *conf);

#endif
