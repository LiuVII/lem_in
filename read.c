/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 00:00:36 by mfilipch          #+#    #+#             */
/*   Updated: 2016/12/17 00:00:38 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

/*
**Rec type of line to list id, determine number of rooms, start and finish
**pf("LINE: %s | FLAG %d | currect ROOM_NUM %d\n", line, *flag, afarm->rnum);
*/

int		ft_line_id(char *line, int *fl, t_graph *afarm)
{
	if (!(*fl) && (*fl = 2) && (*line))
		return (0);
	else if (!ft_strcmp(line, "##start") && (*fl = -1))
		return (-1);
	else if (!ft_strcmp(line, "##end") && (*fl = 1))
		return (1);
	else if (*line != '#' && *fl == -1 && ft_check_rnb(line, 0, 0) > 0
		&& (afarm->start == -1) && (*fl = 2)
		&& (afarm->start = afarm->rnum) >= 0 && ++(afarm->rnum))
		return (2);
	else if (*line != '#' && *fl == 1 && ft_check_rnb(line, 0, 0) > 0
		&& (afarm->finish == -1) && (*fl = 2)
		&& (afarm->finish = afarm->rnum) >= 0 && ++(afarm->rnum))
		return (2);
	else if (*line != '#' && *fl > 1 && ft_check_rnb(line, 0, 0) > 0
		&& ++(afarm->rnum))
		return (2);
	else if (*line != '#' && ft_check_rnb(line, 0, 0) < 0 && (*fl = -2))
		return (3);
	else if (*line == '#')
		return (10);
	return (-10);
}

void	ft_read_to_list(t_list **list, int ret, int flag, t_graph *afarm)
{
	t_list	*tmp;
	char	*line;

	while ((ret = get_next_line(0, &line)) > 0)
	{
		if (!(*list))
		{
			if (!(*list = ft_lstnew(line, ft_strlen(line) + 1)))
				ft_free_n_exit(afarm->spine[4], line, list, -5);
			tmp = *list;
		}
		else
		{
			if (!(tmp->next = ft_lstnew(line, ft_strlen(line) + 1)))
				ft_free_n_exit(afarm->spine[4], line, list, -5);
			tmp = tmp->next;
		}
		if ((tmp->id = ft_line_id(line, &flag, afarm)) == -10)
			ft_free_n_exit(afarm->spine[4], line, list, -10);
		ft_printf("%s\n", line);
		free(line);
	}
	(tmp) ? tmp->next = NULL : 0;
	free(line);
	(ret == -1) ? ft_free_n_exit(afarm->spine[4], NULL, list, -4) : 0;
}

int		ft_rec_bond(t_list *list, t_graph *afarm, int i, int j)
{
	char	**arr;

	if (!(arr = ft_strsplit(list->content, '-')))
		return (-1);
	while (++i < afarm->rnum)
	{
		if (j == -1 && (!ft_strcmp((afarm->rnames)[i], arr[0])) && (j = i) >= 0)
			i = -1;
		else if (j != -1 && (!ft_strcmp((afarm->rnames)[i], arr[1])))
			break ;
	}
	ft_mapfree(&arr);
	if (i == afarm->rnum || i == j)
		return (-1);
	(afarm->w_matx)[i][j] = 1;
	(afarm->w_matx)[j][i] = 1;
	return (0);
}

/*
** printf("TEST: writing to afarm %d\n", i + 1);
*/

void	ft_read(t_graph *afarm, t_list *list, int i, int j)
{
	t_list	*tmp;

	ft_read_to_list(&list, 0, 0, afarm);
	afarm->w_matx = (int**)malloc(sizeof(int*) * afarm->rnum);
	afarm->rnames = (char**)malloc(sizeof(char*) * (afarm->rnum + 1));
	(afarm->rnames)[afarm->rnum] = 0;
	while ((j = -1) && ++i < afarm->rnum &&
		((afarm->w_matx)[i] = (int*)malloc(sizeof(int) * afarm->rnum)))
		while (++j < afarm->rnum)
			(afarm->w_matx)[i][j] = 0;
	tmp = list;
	while (tmp)
	{
		if (!tmp->id)
			(!(afarm->anum)) ? afarm->anum = ft_atoi(tmp->content)
		: ft_free_n_exit(afarm->spine[4], NULL, &list, -3);
		else if (tmp->id == 2)
			(afarm->rnames)[++j] = ft_strsub(tmp->content, 0,
				ft_strnchr(tmp->content, ft_strlen(tmp->content), ' '));
		else if (tmp->id == 3)
			(ft_rec_bond(tmp, afarm, -1, -1))
		? ft_free_n_exit(afarm->spine[4], NULL, &list, -6) : 0;
		tmp = tmp->next;
	}
	ft_lstclr(&list);
}
