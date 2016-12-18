/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 00:00:45 by mfilipch          #+#    #+#             */
/*   Updated: 2016/12/17 00:00:46 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

int		ft_isempty(int *arr, int n)
{
	int		i;

	i = -1;
	while (++i < n)
		if (arr[i] > 0)
			return (1);
	return (0);
}

int		ft_get_mindist_rind(t_graph *afarm)
{
	int		i;
	int		j;
	int		min_dist;

	i = -1;
	j = -1;
	min_dist = afarm->rnum + afarm->anum + 1;
	while (++i < afarm->rnum)
		if ((afarm->q)[i] && (afarm->d_matx)[i] < min_dist)
			{
				j = i;
				min_dist = (afarm->d_matx)[i];
			}
	return (j);
}

int		ft_find_path(t_graph *afarm)
{
	int		i;
	int		j;
	int		tmp_dist;

	i = -1;
	while (++i < afarm->rnum)
	{
		(afarm->q)[i] = 1;
		(afarm->s)[i] = 0;
		(afarm->d_matx)[i] = afarm->rnum + afarm->anum + 1;
	}
	(afarm->d_matx)[afarm->finish] = 0;
	while (ft_isempty(afarm->q, afarm->rnum))
	{
		i = ft_get_mindist_rind(afarm);
		// printf("%s: %d\n", (afarm->rnames)[i], (afarm->d_matx)[i]);
		(afarm->q)[i] = 0;
		(afarm->s)[i] = 1;
		j = -1;
		while (++j < afarm->rnum)
			if ((afarm->w_matx)[i][j] == 1)
			{
				tmp_dist = (afarm->d_matx)[i] + 1 + ((i != afarm->start) ? (afarm->aq)[i] : 0);
				if (tmp_dist < (afarm->d_matx)[j])
					(afarm->d_matx)[j] = tmp_dist;
			}
	}
	return (0);
}

void	ft_print_changes(t_graph *afarm)
{
	int		i;

	i = -1;
	while (++i < afarm->anum)
	{
		ft_putchar('L');
		ft_putnbr(i);
		ft_putchar('-');
		if ((afarm->anr)[i] != -1)
			ft_putstr((afarm->rnames)[(afarm->anr)[i]]);
		else
			ft_putstr((afarm->rnames)[(afarm->acr)[i]]);
		ft_putchar(' ');
	}
	ft_putchar('\n');
}

// int		ft_solve_farm(t_graph *afarm)
int		ft_iter_farm(t_graph *afarm)
{
	int		i;
	int		j;
	int		next_r;

	i = -1;
	while (++i < afarm->anum)
	{
		(afarm->anr)[i] = -1;
		ft_find_path(afarm);
		j = -1;
		while (++j < afarm->rnum)
		{
			printf("room: %s dist: %d\n", (afarm->rnames)[j], (afarm->d_matx)[j]);
		}
		printf("\n");
		j = -1;
		printf("curr room: %s\n", (afarm->rnames)[(afarm->acr)[i]]);
		next_r = (afarm->acr)[i];
		while (++j < afarm->rnum)
			if (afarm->w_matx[(afarm->acr)[i]][j] == 1)
				if ((afarm->d_matx)[j] < (afarm->d_matx)[next_r])
					next_r = j;
		if (!(afarm->aq)[next_r] && next_r != (afarm->acr)[i])
		{
			(afarm->anr)[i] = next_r;
			(afarm->as)[next_r]++;
			(afarm->as)[(afarm->acr)[i]]--;
		}
		(afarm->aq)[next_r]++;
		(afarm->aq)[(afarm->acr)[i]]--;
	}
	ft_print_changes(afarm);
	return (0);
}

int		ft_solve_farm(t_graph *afarm)
{
	int		iter;
	int		i;	
	
	iter = 4;
	while (iter-- && (afarm->as)[afarm->finish] != afarm->anum)
	{
		ft_iter_farm(afarm);
		i = -1;
		while (++i < afarm->anum)
			((afarm->anr)[i] >= 0) ? (afarm->acr)[i] = (afarm->anr)[i] : 0;
	}
	return (0);
}