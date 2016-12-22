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

/*
** pf("step %d, r-nr: %s - %s\n", step, afarm->rnames[room], afarm->rnames[i]);
** printf("bef first cont %d\n", list->id);
*/

void	ft_find_path(t_graph *afarm, int room, t_list *list, int step)
{
	int		i;
	int		j;

	j = 0;
	if (room != afarm->finish && (i = -1))
		while (++i < afarm->rnum)
			if ((afarm->w_matx)[room][i] == 1 && afarm->q[i])
			{
				if (!j && ++j && (list->id = step + 1))
					((int*)(list->content))[step] = i;
				else
				{
					while (list->next)
						list = list->next;
					list->next = ft_create_lnode(step + 1, afarm);
					ft_memcpy(list->next->content, list->content,
						sizeof(int) * (afarm->rnum + afarm->anum));
					((int*)(list->next->content))[step] = i;
					list = list->next;
				}
				afarm->q[i] = 0;
				ft_find_path(afarm, i, list, step + 1);
				afarm->q[i] = 1;
			}
	(room == afarm->finish) ? list->c_s = 1 : 0;
}

/*
** convert list to array
**		calc size of the list, allocate array, copy list content to array
*/

int		ft_list_to_array(t_graph *afarm, t_list *list, int i, int check)
{
	t_list	*tmp;
	int		j;

	tmp = list;
	while (tmp && ++i)
		tmp = tmp->next;
	afarm->pnum = i;
	afarm->parr = (t_apath*)malloc(sizeof(t_apath) * afarm->pnum);
	tmp = list;
	i = -1;
	while (++i < afarm->pnum)
	{
		(afarm->parr[i]).rooms = ((int*)tmp->content);
		(afarm->parr[i]).n = tmp->id - 1;
		(afarm->parr[i]).incr = 0;
		(afarm->parr[i]).enable = tmp->c_s;
		check += tmp->c_s;
		(afarm->parr[i]).cross_p = (int*)malloc(sizeof(int) * afarm->pnum);
		j = -1;
		while (++j < afarm->pnum)
			(afarm->parr[i]).cross_p[j] = 0;
		tmp = tmp->next;
	}
	return (check);
}

/*
** select path and assign numbers of intersected paths
** 	reset all rooms | disable rooms for a selected path |
** 	select path that has higher index then selected (cross ref check)
** 		check rooms if any of them are disabled
** 		if at least one is disabled add path number to array of intersection
** 		belonging to initially selected path (cross ref of course)
*/

void	ft_find_intersections(t_graph *afarm)
{
	int		i;
	int		j;
	int		l;

	i = -1;
	while (++i < afarm->pnum)
		if ((afarm->parr[i]).enable)
		{
			j = -1;
			while (++j < afarm->rnum)
				afarm->q[j] = 1;
			j = -1;
			while (++j < (afarm->parr[i]).n)
				afarm->q[(afarm->parr[i]).rooms[j]] = 0;
			l = i;
			while (++l < afarm->pnum)
				if ((afarm->parr[l]).enable && (j = -1))
					while (++j < (afarm->parr[l]).n)
						if (afarm->q[(afarm->parr[l]).rooms[j]] == 0)
						{
							(afarm->parr[i]).cross_p[l] = 1;
							(afarm->parr[l]).cross_p[i] = 1;
							break ;
						}
		}
}

/*
** if current ant is the last one and current solution has less steps than
** 		previous minimum => record it | for ant | select available path |
** disable intersected paths | assign selected path to selected ant |
** renew number of steps of current soulution to the MAX of all paths selected |
** increment path usage| call recursion for the next ant| decrement path usage |
** enable intersected paths if current one was not already used before
*/

void	ft_find_best(t_graph *afarm, int *min, int curr, int ant)
{
	int		i;
	int		j;
	int		t_curr;

	if (ant == afarm->anum && curr < *min && (i = -1)
		&& (*min = curr))
		while (++i < afarm->anum)
			afarm->as[i] = afarm->aq[i];
	else if (ant != afarm->anum && curr < *min && (i = -1))
		while (++i < afarm->pnum)
			if ((afarm->parr[i]).enable > 0 && (j = -1))
			{
				while (++j < afarm->pnum)
					if ((afarm->parr[i]).cross_p[j] == 1)
						(afarm->parr[j]).enable--;
				(afarm->aq)[ant] = i;
				t_curr = MAX((afarm->parr[i]).n + (afarm->parr[i]).incr, curr);
				(afarm->parr[i]).incr++;
				ft_find_best(afarm, min, t_curr, ant + 1);
				(afarm->parr[i]).incr--;
				j = -1;
				while (++j < afarm->pnum)
					if ((afarm->parr[i]).cross_p[j] == 1)
						(afarm->parr[j]).enable++;
			}
}

/*
** create first list element
** find all possible paths
** convert list to arrray and find intersections betwern paths
** 	find best solution, set as maximum possible distance between any two nodes
*/

int		ft_solve_farm(t_graph *afarm)
{
	int		j;
	int		min;
	t_list	*list;

	list = ft_create_lnode(0, afarm);
	j = -1;
	while (++j < afarm->rnum)
		afarm->q[j] = 1;
	afarm->q[afarm->start] = 0;
	ft_find_path(afarm, afarm->start, list, 0);
	ft_lstprint(afarm, list);
	if (ft_list_to_array(afarm, list, 0, 0))
	{
		ft_find_intersections(afarm);
		ft_print_intsecs(afarm);
		min = afarm->rnum + afarm->anum - 1;
		ft_find_best(afarm, &min, 0, 0);
		ft_print_solution(afarm, min);
		ft_print_steps(afarm, min + 1, 0, NULL);
	}
	ft_lstclr(&list);
	return (0);
}
