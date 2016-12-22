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
*/

int		ft_line_id(char *line, int *flag, t_graph *afarm)
{
	// printf("LINE: %s | FLAG %d | currect ROOM_NUM %d\n", line, *flag, afarm->rnum);
	if (!(*flag) && (*flag = 2))
		return (0);
	else if (!ft_strcmp(line, "##start") && (*flag = -1))
		return (-1);
	else if (!ft_strcmp(line, "##end") && (*flag = 1))
		return (1);
	else if (*line != '#' && *flag == -1 && ft_check_rnb(line, 0) > 0 && (*flag = 2)
		&& (afarm->start = afarm->rnum) >= 0 && ++(afarm->rnum))
		return (2);
	else if (*line != '#' && *flag == 1 && ft_check_rnb(line, 0) > 0 && (*flag = 2)
		&& (afarm->finish = afarm->rnum) >= 0 && ++(afarm->rnum))
		return (2);
	else if (*line != '#' && *flag > 1 && ft_check_rnb(line, 0) > 0
		&& afarm->rnum++)
		return (2);
	else if (*line != '#' && ft_check_rnb(line, 0) < 0 && (*flag = -2))
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
				ft_free_n_exit(line, list, -5);
			tmp = *list;
		}
		else
		{
			if (!(tmp->next = ft_lstnew(line, ft_strlen(line) + 1)))
				ft_free_n_exit(line, list, -5);
			tmp = tmp->next;
		}
		if ((tmp->id = ft_line_id(line, &flag, afarm)) == -10)
			ft_free_n_exit(line, list, -10);
		printf("%s\n", line);
		free(line);
	}
	tmp->next = NULL;
	free(line);
	(ret == -1) ? ft_free_n_exit(NULL, list, -4) : 0;
}

int		ft_rec_bond(t_list *list, t_graph *afarm, int i, int j)
{
	char	**arr;

	if (!(arr = ft_strsplit(list->content,'-')))
		return (0);
	i = -1;
	j = -1;
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

int		ft_read(t_graph *afarm, t_list *list, int i, int j)
{;
	t_list	*tmp;

	ft_read_to_list(&list, 0, 0, afarm);
	afarm->w_matx = (int**)malloc(sizeof(int*) * afarm->rnum);
	afarm->rnames = (char**)malloc(sizeof(char*) * (afarm->rnum + 1));
	(afarm->rnames)[afarm->rnum] = 0;
	while (++i < afarm->rnum && (j = -1)
		&& ((afarm->w_matx)[i] = (int*)malloc(sizeof(int) * afarm->rnum)))
		while (++j < afarm->rnum)
			(afarm->w_matx)[i][j] = 0;
	i = -1;
	// printf("TEST: reading\n");
	tmp = list;
	while (tmp)
	{
		// printf("TEST: writing to afarm %d\n", i + 1);
		// (tmp->content) ?  printf("tmp elem%s\n", tmp->content) : 0;
		if (!tmp->id)
			(!(afarm->anum)) ? afarm->anum = ft_atoi(tmp->content) : ft_free_n_exit(NULL, &list, -3);
		else if (tmp->id == 2)
			(afarm->rnames)[++i] = ft_strsub(tmp->content, 0,
				ft_strnchr(tmp->content, ft_strlen(tmp->content), ' '));
		else if (tmp->id == 3)
			ft_rec_bond(tmp, afarm, -1, -1);
		tmp = tmp->next;
	}
	// printf("TEST: writing finished\n");
	ft_lstclr(&list);
	return (0);
}
