/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   servfunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 03:55:15 by mfilipch          #+#    #+#             */
/*   Updated: 2016/12/22 03:55:21 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

t_list	*ft_create_lnode(int step, t_graph *afarm)
{
	t_list	*new;

	new = ft_lstnew(NULL, 0);
	new->content = (int*)malloc(sizeof(int) * (afarm->rnum + afarm->anum));
	new->id = step;
	new->c_s = 0;
	return (new);
}

/*
** set queue to have initial occupancy of the rooms
** set all ants to a start room (index of path)
*/

void	ft_printsteps_prepare(t_graph *afarm)
{
	int		i;
	int		j;

	j = -1;
	while (++j < afarm->rnum)
		afarm->q[j] = 0;
	afarm->q[afarm->start] = afarm->anum;
	i = -1;
	while (++i < afarm->anum)
		afarm->aq[i] = 0;
}

void	ft_clear_farm(t_graph *afarm)
{
	int		i;

	i = -1;
	while (++i < afarm->rnum)
	{
		free((afarm->rnames)[i]);
		free((afarm->w_matx)[i]);
	}
	free(afarm->rnames);
	free(afarm->w_matx);
	free(afarm->q);
	free(afarm->s);
	free(afarm->as);
	free(afarm->aq);
	i = -1;
	if (afarm->parr)
		while (++i < afarm->pnum)
			free(afarm->parr[i].cross_p);
	free(afarm->parr);
}

void	ft_free_n_exit(char *line, t_list **list, int err)
{
	printf("Error func start with code: %d\n", err);
	(line) ? free(line) : 0;
	(list && *list) ? ft_lstclr(list) : 0;
	if (err)
	{
		ft_putnbr_fd(err, 2);
		ft_putstr_fd(" Error\n", 2);
	}
	(err) ? exit(-1) : exit(0);
}

void	ft_farm_init(t_graph *afarm)
{
	int		i;

	afarm->anum = 0;
	afarm->rnum = 0;
	afarm->start = 0;
	afarm->finish = 0;
	afarm->pnum = 0;
	afarm->w_matx = NULL;
	afarm->rnames = NULL;
	afarm->q = NULL;
	afarm->s = NULL;
	afarm->aq = NULL;
	afarm->as = NULL;
	afarm->parr = NULL;
	i = -1;
	while (++i < 5)
		afarm->spine[i] = 0;
}
