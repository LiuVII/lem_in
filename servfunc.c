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

void	ft_free_n_exit(int flag, char *line, t_list **list, int err)
{
	(line) ? free(line) : 0;
	(list && *list) ? ft_lstclr(list) : 0;
	(err) ? ft_putstr_fd("ERROR\n", 2) : 0;
	if (flag)
	{
		(err == -1) ? ft_putstr_fd("Wrong arguments\n\
			usage: ./lem_in [-s, -p, -i, -n, -e] {input}\n", 2) : 0;
		(err == -2) ? ft_putstr_fd("Invalid map\n", 2) : 0;
		(err == -6) ? ft_putstr_fd("Invalid format\
			or self connection\n", 2) : 0;
		(err == -10) ? ft_putstr_fd("Invalid map character\n", 2) : 0;
		(err == -5) ? ft_putstr_fd("Failed allocation\n", 2) : 0;
		(err == -4) ? ft_putstr_fd("Failed reading an input\n", 2) : 0;
		(err == -3) ? ft_putstr_fd("Number of ants is invalid\n", 2) : 0;
		(err == -7) ? ft_putstr_fd("No possible solution\n", 2) : 0;
	}
	(err) ? exit(-1) : exit(0);
}

void	ft_farm_init(t_graph *afarm)
{
	int		i;

	afarm->anum = 0;
	afarm->rnum = 0;
	afarm->start = -1;
	afarm->finish = -1;
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
