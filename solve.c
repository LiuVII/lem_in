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
			return (i);
	return (-1);
}

int		ft_isfull(int *arr, int n)
{
	int		i;
	int		sum;

	i = -1;
	sum = 0;
	while (++i < n)
		if (arr[i] != 0)
			sum++;
	return (sum);
}

void	ft_print_changes(t_graph *afarm)
{
	int		i;

	i = -1;
	while (++i < afarm->anum)
		if ((afarm->anr)[i] != -1)
		{
			ft_putchar('L');
			ft_putnbr(i + 1);
			ft_putchar('-');
			ft_putstr((afarm->rnames)[(afarm->anr)[i]]);
			ft_putchar(' ');
		}
		else
		{
			ft_putchar('L');
			ft_putnbr(i + 1);
			ft_putchar('-');
			ft_putstr((afarm->rnames)[(afarm->acr)[i]]);
			ft_putchar(' ');
		}
	ft_putchar('\n');
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

void	ft_find_path(t_graph *afarm, int i)
{
	int		j;
	int		tmp_dist;

	while (++i < afarm->rnum)
	{
		(afarm->q)[i] = 1;
		(afarm->s)[i] = 0;
		(afarm->d_matx)[i] = afarm->rnum + afarm->anum + 1;
	}
	(afarm->d_matx)[afarm->finish] = 0;
	while (ft_isempty(afarm->q, afarm->rnum) >= 0)
	{
		i = ft_get_mindist_rind(afarm);
		// printf("%s: %d| q:%d\n", (afarm->rnames)[i], (afarm->d_matx)[i], (afarm->aq)[i]);
		(afarm->q)[i] = 0;
		(afarm->s)[i] = 1;
		j = -1;
		while (++j < afarm->rnum)
			if ((afarm->w_matx)[i][j] == 1)
			{
				tmp_dist = (afarm->d_matx)[i] + 1 + ((j != afarm->finish) ? (afarm->aq)[j] : 0);
				if (tmp_dist < (afarm->d_matx)[j])
					(afarm->d_matx)[j] = tmp_dist;
			}
	}
}

int		ft_min_path(t_graph *afarm, int room)
{
	int		i;
	int		tmp_dist;	

	i = -1;
	tmp_dist = (afarm->d_matx)[room];
	while (++i < afarm->rnum)
		if ((afarm->w_matx)[room][i] == 1)
			if ((afarm->d_matx)[i] < tmp_dist)
				tmp_dist = (afarm->d_matx)[i];
	return (tmp_dist);
}

void	ft_apply_choice(int i, t_graph *afarm, int curr_r, int next_r)
{
	if ((next_r == afarm->finish || !(afarm->as)[next_r]) && next_r != curr_r)
	{
		(afarm->acr)[i] = next_r;
		(afarm->as)[next_r]++;
		(afarm->as)[curr_r]--;
		(curr_r != afarm->start) ? (afarm->aq)[curr_r]-- : 0;
	}
	(next_r != afarm->finish) ? (afarm->aq)[next_r]++ : 0;
}

void	ft_rollback_choice(int i, t_graph *afarm, int curr_r, int next_r)
{
	(next_r != afarm->finish) ? (afarm->aq)[next_r]-- : 0;
	if ((afarm->acr)[i] == next_r)
	{
		(afarm->acr)[i] = curr_r;
		(afarm->as)[next_r]--;
		(afarm->as)[curr_r]++;
		(curr_r != afarm->start) ? (afarm->aq)[curr_r]++ : 0;
	}
}

int		ft_iter_farm(int *ant_arr, t_graph *afarm, int steps, int rchoice, int check)
{
	int		i; /* current ant*/
	int		j;
	int		next_r;
	int		curr_r;
	int		min_dist;
	int		stepinc;
	// int		curr_ant;

	// exit condition when all ants reach finish
	if (afarm->as[afarm->finish] == afarm->anum)
		return (steps);
	// pick first availble ant and if all ants made thier move or decided to wait, reset environment for another step
	if ((ft_isempty(ant_arr, afarm->anum)) < 0)
	{
		// increase number of steps to the goal
		steps++;
		// reset available ants
		j = -1;
		while (++j < afarm->anum)
			if ((afarm->acr)[j] != afarm->finish)
				ant_arr[j] = 1;
	}
	j = -1;
	while (++j < afarm->anum)
		if (ant_arr[j] && (afarm->acr)[j] != afarm->finish)
			break ;
	i = j;
	ant_arr[i] = 0;
	curr_r = (afarm->acr)[i];
	//	calculate available paths & find min_dist
	// printf("steps: %d| ant: %d curr_r %s\n", steps, i, afarm->rnames[curr_r]);
	ft_find_path(afarm, -1);
	min_dist = ft_min_path(afarm, curr_r);
	// printf("min_dist %d\n", min_dist);
	// select and explore all paths of min dist
	next_r = -1;
	stepinc = -1;
	while (++next_r < afarm->rnum)
		if (afarm->w_matx[curr_r][next_r] == 1)
			if ((afarm->d_matx)[next_r] == min_dist)
			{
				//apply changes
				// printf("next_r %s\n", afarm->rnames[next_r]);
				ft_apply_choice(i, afarm, curr_r, next_r);
				// printf("queue %d, changed curr_r to %s\n", (afarm->aq)[next_r], afarm->rnames[next_r]);
				//call recursion to find number of steps in path
				if (((j = ft_iter_farm(ant_arr, afarm, steps, -1, 1)) < stepinc && j >= 0) || stepinc == -1)
				{
					rchoice = next_r;
					stepinc = j;
				}
				//roll back changes
				ft_rollback_choice(i, afarm, curr_r, next_r);
				// (afarm->acr)[i] = curr_r;
				// printf("steps: %d, ant: %d, rollback next_r %s\n", steps, i, afarm->rnames[next_r]);
			}
	ant_arr[i] = 1;
	if (ft_isfull(ant_arr, afarm->anum) + (afarm->as)[afarm->finish] == afarm->anum)
	{
		j = -1;
		while (++j < afarm->anum)
			ant_arr[j] = 0;
	}
	if (steps > 1 || check)
		return (stepinc);
	return (rchoice);
}

int		ft_solve_farm(t_graph *afarm)
{
	int		iter;
	int		i;
	int		j;
	int 	*ant_arr;
	int		rchoice;
	
	iter = 12;
	ant_arr = (int*)malloc(sizeof(int) * afarm->anum);
	i = -1;
	while (++i < afarm->anum)
		ant_arr[i] = 0;
	while (iter-- && (afarm->as)[afarm->finish] != afarm->anum)
	{
		rchoice = ft_iter_farm(ant_arr, afarm, 0, -1, 0);
		if ((ft_isempty(ant_arr, afarm->anum)) < 0)
		{
			// reset available ants
			j = -1;
			while (++j < afarm->anum)
				if ((afarm->acr)[j] != afarm->finish)
					ant_arr[j] = 1;
		}
		j = -1;
		while (++j < afarm->anum)
			if (ant_arr[j] && (afarm->acr)[j] != afarm->finish)
				break ;
		i = j;
		printf("Ant: %d, Curr_R: %s, Choice: %s\n",i, afarm->rnames[(afarm->acr)[i]], afarm->rnames[rchoice]);
		ant_arr[i] = 0;
		ft_apply_choice(i, afarm, (afarm->acr)[i], rchoice);
	}
	return (0);
}
