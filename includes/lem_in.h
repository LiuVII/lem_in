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


typedef struct	s_arlist
{
	int				n;
	int				*rooms;
	int				*shift;
	struct s_arlist	*next;
}				t_arlist;

typedef struct	s_graph
{
	int		anum;
	int		rnum;
	int		start;
	int		finish;
	int		**w_matx;
	int		*d_matx;
	int		*dr_matx;
	char	**rnames;
	int		*q;
	int		*s;
	int		*aq;
	int		*as;
	int		*acr;
	int		*anr;
	int		mdist;
}				t_graph;

int				ft_solve_farm(t_graph *afarm);

#endif
