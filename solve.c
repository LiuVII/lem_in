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

//REBUILD
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

//CREATE ARRAYS
void	ft_find_best(t_graph *afarm, t_list *list, int i, int best_sol)
{
	int		path_n;
	t_list	*tmp;

	while (++i < afarm->anum)
	{
		path_n = ft_min_path(list);
		afarm->as[i] = path_n;
		afarm->path_s[path_n]++;
	}
}

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


int		ft_solve_farm(t_graph *afarm)
{
	int		iter;
	int		i;
	// int		j;
	t_list *list;
	
	iter = 1;
	i = -1;
	afarm->mdist = ft_num_path(afarm->d_matx, afarm, -1, afarm->start);
	printf("MAX DIST%d\n", afarm->mdist);
	ft_num_path(afarm->dr_matx, afarm, -1, afarm->finish);
	list = ft_lstnew(NULL, 0);
	list->content = (int*)malloc(sizeof(int) * (afarm->rnum + afarm->anum));
	list->id = 0;
	list->c_s = 0;
	ft_find_path(afarm, afarm->start, list, 0);
	// NEEDED FUNCTION to select only unique path, indicate ID by list->c_s;
	ft_lstprint(afarm, list);
	// ft_lstclr(&list);
	// while (iter-- && (afarm->as)[afarm->finish] != afarm->anum)
	// {
	// }
	return (0);
}
