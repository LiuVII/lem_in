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

// void	ft_print_changes(t_graph *afarm)
// {
// 	int		i;

// 	i = -1;
// 	while (++i < afarm->anum)
// 		if ((afarm->anr)[i] != -1)
// 		{
// 			ft_putchar('L');
// 			ft_putnbr(i + 1);
// 			ft_putchar('-');
// 			ft_putstr((afarm->rnames)[(afarm->anr)[i]]);
// 			ft_putchar(' ');
// 		}
// 		else
// 		{
// 			ft_putchar('L');
// 			ft_putnbr(i + 1);
// 			ft_putchar('-');
// 			ft_putstr((afarm->rnames)[(afarm->acr)[i]]);
// 			ft_putchar(' ');
// 		}
// 	ft_putchar('\n');
// }

int		ft_get_mindist_rind(int *darr, t_graph *afarm)
{
	int		i;
	int		j;
	int		min_dist;

	i = -1;
	j = -1;
	min_dist = afarm->rnum + afarm->anum + 1;
	while (++i < afarm->rnum)
		if ((afarm->q)[i] && (darr)[i] < min_dist)
			{
				j = i;
				min_dist = (darr)[i];
			}
	return (j);
}

int		ft_num_path(int *darr, t_graph *afarm, int i, int start)
{
	int		j;
	int		tmp_dist;
	int		max_dist;

	while (++i < afarm->rnum)
	{
		(afarm->q)[i] = 1;
		(afarm->s)[i] = 0;
		(darr)[i] = afarm->rnum + afarm->anum + 1;
	}
	(darr)[start] = 0;
	max_dist = 0;
	while (ft_isempty(afarm->q, afarm->rnum) >= 0)
	{
		i = ft_get_mindist_rind(darr, afarm);
		printf("%s: %d|\n", (afarm->rnames)[i], (darr)[i]);
		(afarm->q)[i] = 0;
		(afarm->s)[i] = 1;
		j = -1;
		while (++j < afarm->rnum)
			if ((afarm->w_matx)[i][j] == 1)
			{
				tmp_dist = (darr)[i] + 1;
				if (tmp_dist < (darr)[j])
				{
					(darr)[j] = tmp_dist;
					if (max_dist < tmp_dist)
						max_dist = tmp_dist;
				}
			}
	}
	return (max_dist);
}

//rebuild using visited nodes
void	ft_find_path(t_graph *afarm, int room, t_list *list, int step)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (room != afarm->finish)
	{
		while (++i < afarm->rnum)
			if ((afarm->w_matx)[room][i] == 1 &&
				(afarm->d_matx[i] > afarm->d_matx[room] ||
					afarm->dr_matx[i] < afarm->dr_matx[room]))
			{
				printf("step %d, r-nr: %s - %s\n", step, afarm->rnames[room], afarm->rnames[i]);
				if (!j && ++j)
				{
					printf("bef first cont %d\n", list->id);
					((int*)(list->content))[step] = i;
					list->id = step + 1;
				}
				else
				{
					printf("bef next\n");
					while (list->next)
						list = list->next;
					list->next = ft_lstnew(NULL, 0);
					list->next->content = (int*)malloc(sizeof(int) * (afarm->rnum + afarm->anum));
					printf("bef memcpy\n");
					list->next->content = memcpy(list->next->content, list->content, sizeof(int) * (afarm->rnum + afarm->anum));
					printf("after memcpy %d\n", step);
					((int*)(list->next->content))[step] = i;
					list->next->id = step + 1;
					list->next->c_s = 0;
					list = list->next;
				}
				ft_find_path(afarm, i, list, step + 1);
			}
	}
	else
		list->c_s = 1;
}

// void	ft_find_best(t_graph *afarm, t_list *list)
// {
// 	int		i;
// 	int		j;
// 	int		min;
// 	t_list	*tmp;
// 	int		path_n;

// 	i = -1;
// 	while (++i < afarm->anum)
// 	{
// 		tmp = list;
// 		j = -1;
// 		min = -1;
// 		while (tmp)
// 		{
// 			j++;
// 			if (tmp->c_s && tmp->id + afarm->path_s[path_n] < min || min == -1)
// 			{
// 				min = tmp->id + afarm->path_s[path_n];
// 				path_n = j;
// 			}
// 			tmp = tmp->next;
// 		}
// 		afarm->as[i] = path_n;
// 		afarm->path_s[path_n]++;
// 	}
// }

void	ft_lstprint(t_graph *afarm, t_list *list)
{
	int i;

	while (list)
	{
		i = -1;
		printf("arr size: %d, is a path %zu\narr: ", list->id, list->c_s);
		while (++i < list->id)
			printf("%s ", afarm->rnames[((int*)list->content)[i]]);
		printf("\n");
		list = list->next;
	}
}


void	ft_list_to_array(t_graph *afarm, t_list *list)
{
	t_list	*tmp;
	int		i;
	int		j;

	//convert list to array
	tmp = list;
	i = 0;
	while (tmp && ++i)
		tmp = tmp->next;
	//initialize size of the paths array
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
		(afarm->parr[i]).cross_p = (int*)malloc(sizeof(int) * afarm->pnum);
		j = -1;
		while (++j < afarm->pnum)
			(afarm->parr[i]).cross_p[j] = 0;
		tmp = tmp->next;
	}
}

void	ft_find_intersections(t_graph *afarm)
{
	int		i;
	int		j;
	int		l;

	//select path and assign numbers of intersected paths
	i = -1;
	while (++i < afarm->pnum)
		if ((afarm->parr[i]).enable)
	{
		j = -1;
		//reset all rooms
		while (++j < afarm->rnum)
			afarm->q[j] = 1;
		// disable rooms for a selected path
		j = -1;
		// printf("path: %d num of rooms %d\n", i, (afarm->parr[i]).n);
		while (++j < (afarm->parr[i]).n)
			afarm->q[(afarm->parr[i]).rooms[j]] = 0;
		l = i;
		// select path that has higher index then selected (because of cross reference check)
		while (++l < afarm->pnum)
			if ((afarm->parr[l]).enable)
		{
			j = -1;
			// check rooms if any of them are disabled
			while (++j < (afarm->parr[l]).n)
				if (afarm->q[(afarm->parr[l]).rooms[j]] == 0)
				{
					// if at least one is disabled add path number to array of intersection belonging to initially selected path
					(afarm->parr[i]).cross_p[l]	= 1;
					// it should be cross reference of course
					(afarm->parr[l]).cross_p[i]	= 1;
					break ;
				}
		}
	}
}

void	ft_print_solution(t_graph *afarm, int steps)
{
	int		i;
	int		j;
	int		pn;

	i = -1;
	printf("Steps: %d\n", steps + 1);
	while (++i < afarm->anum)
	{
		pn = afarm->as[i];
		printf("ANT: %d|path: %d|", i, pn);
		j = -1;
		while (++j < afarm->parr[pn].n + 1)
		{
			printf("%s ", afarm->rnames[(afarm->parr[pn].rooms)[j]]);
		}
		printf("\n");
	}
}

void	ft_find_best(t_graph *afarm, int *min, int curr, int ant)
{
	int		i;
	int		j;
	int		t_curr;

	//if current ant is the last one and current solution has less steps than previous minimum => record it
	if (ant == afarm->anum && curr < *min)
	{
		i = -1;
		*min = curr;
		while (++i < afarm->anum)
			afarm->as[i] = afarm->aq[i];
		// ft_print_solution(afarm, *min);
	}
	else if (ant != afarm->anum && curr < *min)
	{
		//for ant
		i = -1;
		//select available path
		while (++i < afarm->pnum)
			if ((afarm->parr[i]).enable > 0)
			{
				// printf("ant: %d, s_path: %d\n", ant, i);
				//disable intersected paths
				j = -1;
				while (++j < afarm->pnum)
					if ((afarm->parr[i]).cross_p[j]	== 1)
						(afarm->parr[j]).enable--;
				//assign selected path to selected ant
				(afarm->aq)[ant] = i;
				//renew number of steps of current soulution to the MAX of all paths selected
				t_curr = MAX((afarm->parr[i]).n + (afarm->parr[i]).incr, curr);
				//increment usage of the path
				(afarm->parr[i]).incr++;
				//call recursion for the next ant
				ft_find_best(afarm, min, t_curr, ant + 1);
				//decrement usage of the path
				(afarm->parr[i]).incr--;
				//enable intersected paths if current one was not already used before
				// if ((afarm->parr[i]).incr == 0)
				// {
					j = -1;
					while (++j < afarm->pnum)
						if ((afarm->parr[i]).cross_p[j]	== 1)
							(afarm->parr[j]).enable++;
				// }
			}
	}
}

int		ft_solve_farm(t_graph *afarm)
{
	int		iter;
	int		i;
	int		j;
	int		min;
	t_list *list;
	
	iter = 1;
	i = -1;
	j = -1;
	afarm->mdist = ft_num_path(afarm->d_matx, afarm, -1, afarm->start);
	printf("MAX DIST%d\n", afarm->mdist);
	ft_num_path(afarm->dr_matx, afarm, -1, afarm->finish);
	list = ft_lstnew(NULL, 0);
	list->content = (int*)malloc(sizeof(int) * (afarm->rnum + afarm->anum));
	list->id = 0;
	list->c_s = 0;
	ft_find_path(afarm, afarm->start, list, 0);
	ft_lstprint(afarm, list);
	ft_list_to_array(afarm, list);
	ft_find_intersections(afarm);
	i = -1;
	while (++i < afarm->pnum)
	{
		j = -1;
		printf("path: %d|", i);
		while (++j < afarm->pnum)
			printf(" %d",(afarm->parr[i]).cross_p[j]);
		printf("\n");
	}
	//find best solution, set as minimum max dist path, curr = 0, ant = 0
	min = afarm->mdist + afarm->anum - 1;
	ft_find_best(afarm, &min, 0, 0);
	ft_print_solution(afarm, min);
	// ft_lstclr(&list);
	return (0);
}
