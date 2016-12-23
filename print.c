/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/22 03:46:31 by mfilipch          #+#    #+#             */
/*   Updated: 2016/12/22 03:46:32 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	ft_print_farm(t_graph *afarm, int i, int j)
{
	ft_printf("\nANTS: %d\nROOMS NUM: %d\nROOMS:\n", afarm->anum, afarm->rnum);
	while (++i < afarm->rnum)
		ft_printf("%s|", (afarm->rnames)[i]);
	ft_printf("\nstart: %d\nfinish: %d\nBONDS\n", afarm->start, afarm->finish);
	i = -1;
	while (++i < afarm->rnum && (j = -1))
	{
		while (++j < afarm->rnum)
			ft_printf("%d ", (afarm->w_matx)[i][j]);
		ft_printf("\n");
	}
}

void	ft_lstprint(t_graph *afarm, t_list *list)
{
	int		i;
	int		j;

	j = -1;
	ft_printf("\nPATHS FOUND\n");
	while (list)
	{
		i = -1;
		ft_printf("path: %3d |size: %2d |", ++j, list->id);
		while (++i < list->id)
			ft_printf("%3s ", afarm->rnames[((int*)list->content)[i]]);
		ft_printf("\n");
		list = list->next;
	}
}

void	ft_print_solution(t_graph *afarm, int steps)
{
	int		i;
	int		j;
	int		pn;

	i = -1;
	ft_printf("\nSOLUTION\nSteps: %d\n", steps + 1);
	while (++i < afarm->anum)
	{
		pn = afarm->as[i];
		ft_printf("ant: %4d |path: %3d |", i + 1, pn);
		j = -1;
		while (++j < afarm->parr[pn].n + 1)
		{
			ft_printf("%3s ", afarm->rnames[(afarm->parr[pn].rooms)[j]]);
		}
		ft_printf("\n");
	}
}

void	ft_print_steps(t_graph *afarm, int steps, int ctr, t_apath *pn)
{
	int		i;
	int		j;

	ft_printf("\n");
	ft_printsteps_prepare(afarm);
	while (steps-- && (j = -1))
	{
		ctr = 0;
		while (++j < afarm->anum && (pn = &(afarm->parr[afarm->as[j]])))
			if ((afarm->aq[j] == 0 && (pn->rooms[afarm->aq[j]] != afarm->finish
				|| !ctr++)) || (afarm->aq[j] > 0 &&
				(pn->rooms[afarm->aq[j] - 1]) != afarm->finish))
			{
				i = afarm->aq[j];
				if (afarm->q[pn->rooms[i]] == 0 ||
					pn->rooms[i] == afarm->finish)
				{
					afarm->q[pn->rooms[i]]++;
					(i > 0) ? afarm->q[pn->rooms[i - 1]]-- : 0;
					afarm->aq[j]++;
					ft_printf("L%d-%s ", j + 1, afarm->rnames[pn->rooms[i]]);
				}
			}
		ft_printf("\n");
	}
}

void	ft_print_intsecs(t_graph *afarm)
{
	int		i;
	int		j;

	i = -1;
	ft_printf("\nINTERSECTIONS\n");
	while (++i < afarm->pnum)
	{
		j = -1;
		ft_printf("path: %3d, fin: %d | ", i, (afarm->parr[i]).enable);
		while (++j < afarm->pnum)
			ft_printf(" %d", (afarm->parr[i]).cross_p[j]);
		ft_printf("\n");
	}
}
