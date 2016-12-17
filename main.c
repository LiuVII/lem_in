/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 21:32:26 by mfilipch          #+#    #+#             */
/*   Updated: 2016/12/15 21:32:27 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

void	ft_print_farm(t_graph *afarm, int i, int j)
{
	ft_putstr("ANTS:");
	ft_putnbr(afarm->anum);
	ft_putstr("\nROOMS NUM:");
	ft_putnbr(afarm->rnum);	
	ft_putstr("\nROOMS:\n");
	while (++i < afarm->rnum)
	{
		ft_putstr((afarm->rnames)[i]);
		ft_putstr("|");
	}
	ft_putstr("\nstart:");
	ft_putnbr(afarm->start);
	ft_putstr("\nfinish:");
	ft_putnbr(afarm->finish);		
	ft_putstr("\nBONDS\n");
	i = -1;
	while (++i < afarm->rnum && (j = -1))
	{
		while (++j < afarm->rnum)
		{
			ft_putnbr((afarm->w_matx)[i][j]);
			ft_putchar(' ');
		}
		ft_putstr("\n");
	}
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
	free(afarm->d_matx);
	free(afarm->q);
	free(afarm->s);
}


void	ft_free_n_exit(char *line, t_list **list, int err)
{
	(line) ? free(line) : 0;
	(list && *list) ? ft_lstclr(list) : 0;
	if (err)
	{
		ft_putnbr_fd(err, 2);
		ft_putstr_fd(" Error\n", 2);
	}
	(err) ? exit(-1) : exit (0);
}

int		ft_isnum(const char *str)
{
	int			sign;
	long		num;

	sign = 1;
	num = 0;
	if (*str == '+' || *str == '-')
	{
		sign = 44 - *str;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num *= 10;
		num += *str - '0';
		str++;
		if (num + (sign - 1) / 2 > INT_MAX)
			return (0);
	}
	if (*str)
		return (0);
	return (1);
}

/*
**Check if room or bond
*/

int		ft_check_rnb(char *line, int i)
{
	char	**arr;

	if (!(arr = ft_strsplit(line,' ')))
		return (0);
	i = 0;
	while (arr[i])
		i++;
	if (i == 3 && arr[0] && ft_isnum(arr[1]) && ft_isnum(arr[2]))
	{
		ft_mapfree(&arr);
		return (1);
	}
	ft_mapfree(&arr);
	if (!(arr = ft_strsplit(line,'-')))
		return (0);
	i = 0;
	while (arr[i])
		i++;	
	if (i == 2 && arr[0] && arr[1])
	{
		ft_mapfree(&arr);
		return (-1);
	}
	ft_mapfree(&arr);
	return (0);
}

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

	line = NULL;
	flag = 0;
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
		ft_putstr(line);
		ft_putstr("\n");
		free(line);
	}
	tmp->next = NULL;
	free(line);
	(ret == -1) ? ft_free_n_exit(line, list, -4) : 0;
}

int		ft_rec_bond(t_list *list, t_graph *afarm, int i, int j)
{
	char	**arr;

	if (!(arr = ft_strsplit(list->content,'-')))
		return (0);
	i = -1;
	j = -1;
	// printf("bond: %s - %s\n", arr[0], arr[1]);
	while (++i < afarm->rnum)
	{
		if (j == -1 && (!ft_strcmp((afarm->rnames)[i], arr[0])) && (j = i) >= 0)
			i = -1;
		else if ( j != -1 && (!ft_strcmp((afarm->rnames)[i], arr[1])))
			break ;
	}
	if (i == afarm->rnum || i == j)
	{
		ft_mapfree(&arr);
		return (-1);
	}
	// printf("indexes %d %d\n", i, j);
	(afarm->w_matx)[i][j] = 1;
	(afarm->w_matx)[j][i] = 1;
	return (0);
}

int		ft_read(int i, t_graph *afarm, t_list *list)
{
	int		j;

	ft_read_to_list(&list, 0, 0, afarm);
	afarm->w_matx = (int**)malloc(sizeof(int*) * afarm->rnum);
	afarm->d_matx = (int*)malloc(sizeof(int) * afarm->rnum);
	afarm->q = (int*)malloc(sizeof(int) * afarm->rnum);
	afarm->s = (int*)malloc(sizeof(int) * afarm->rnum);
	afarm->aq = (int*)malloc(sizeof(int) * afarm->rnum);
	afarm->as = (int*)malloc(sizeof(int) * afarm->rnum);
	afarm->rnames = (char**)malloc(sizeof(char*) * (afarm->rnum + 1));
	(afarm->rnames)[afarm->rnum] = 0;
	i = -1;
	while (++i < afarm->rnum && (j = -1))
	{
		(afarm->w_matx)[i] = (int*)malloc(sizeof(int) * afarm->rnum);
		(afarm->q)[i] = i;
		(afarm->s)[i] = -1;
		afarm->d_matx[i] = afarm->rnum + afarm->anum + 1;
		(afarm->aq)[i] = 0;		
		(afarm->as)[i] = 0;	
		while (++j < afarm->rnum)
			(afarm->w_matx)[i][j] = 0;
	}
	(afarm->s)[afarm->start] = afarm->start;
	afarm->d_matx[afarm->start] = 0;
	(afarm->as)[i] = afarm->anum;
	i = -1;
	// printf("TEST: reading\n");
	while (list)
	{
		// printf("TEST: writing to afarm %d\n", i + 1);
		// (list->content) ?  printf("LIST elem%s\n", list->content) : 0;
		(list->id == 2 && ++i) ? afarm->q[i] = i : 0;
		if (!list->id)
		{
			// printf("TEST: is it here? %d\n", afarm->anum);
			(!(afarm->anum))
		? afarm->anum = atoi(list->content) : ft_free_n_exit(NULL, &list, -3);
		}
		else if (list->id == 2)
		{
			// printf("LIST elem%s %zu\n", list->content, ft_strnchr(list->content, ft_strlen(list->content), ' '));
			(afarm->rnames)[i] = ft_strsub(list->content, 0,
				ft_strnchr(list->content, ft_strlen(list->content), ' '));
		}
		else if (list->id == 3)
			ft_rec_bond(list, afarm, -1, -1);
		list = list->next;
	}
	// printf("TEST: writing finished\n");
	ft_lstclr(&list);
	return (0);
}

void	ft_farm_init(t_graph *afarm)
{
	afarm->anum = 0;
	afarm->rnum = 0;
	afarm->start = 0;
	afarm->finish = 0;
	afarm->w_matx = NULL;
	afarm->d_matx = NULL;
	afarm->rnames = NULL;
	afarm->q = NULL;
	afarm->s = NULL;
}

int	main(int argc, char const **argv)
{
	t_graph afarm;

	if (argc < 1 || !argv[0])
		return (0);
	ft_farm_init(&afarm);
	ft_read(-1, &afarm, NULL);
	ft_print_farm(&afarm, -1, -1);
	// ft_solve_farm(&afarm);
	ft_clear_farm(&afarm);
	return (0);
}
