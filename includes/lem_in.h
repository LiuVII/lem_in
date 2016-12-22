/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:21:43 by mfilipch          #+#    #+#             */
/*   Updated: 2016/12/01 16:21:45 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# define MALLOC_G(x, y) ((!(x)) ? {return (y);} : 0)
# define MIN(a, b) ((a < b) ? a : b)
# define MAX(a, b) ((a > b) ? a : b)
# define ABS(x) ((x < 0) ? -(x) : x)
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "libft.h"

typedef struct	s_apath
{
	int		n;
	int		incr;
	int		enable;
	int		*rooms;
	int		*cross_p;
}				t_apath;

typedef struct	s_graph
{
	int		anum;
	int		rnum;
	int		start;
	int		finish;
	int		**w_matx;
	char	**rnames;
	int		*q;
	int		*s;
	int		*aq;
	int		*as;
	t_apath	*parr;
	int		pnum;
	int		spine[5];
}				t_graph;

int				ft_solve_farm(t_graph *afarm);

int				ft_read(t_graph *afarm, t_list *list, int i, int j);

int				ft_check_rnb(char *line, int i);

void			ft_clear_farm(t_graph *afarm);
void			ft_free_n_exit(char *line, t_list **list, int err);
void			ft_farm_init(t_graph *afarm);
t_list			*ft_create_lnode(int step, t_graph *afarm);
void			ft_printsteps_prepare(t_graph *afarm);

void			ft_lstprint(t_graph *afarm, t_list *list);
void			ft_print_solution(t_graph *afarm, int steps);
void			ft_print_steps(t_graph *afarm, int steps, int ctr, t_apath *pn);
void			ft_print_intsecs(t_graph *afarm);
void			ft_print_farm(t_graph *afarm, int i, int j);

#endif
