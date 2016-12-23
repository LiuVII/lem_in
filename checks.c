/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.or>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 00:01:29 by mfilipch          #+#    #+#             */
/*   Updated: 2016/12/17 00:01:30 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

int		ft_check_farm(t_graph *afarm)
{
	if (afarm->anum <= 0)
		return (0);
	if (afarm->start == afarm->finish
		|| afarm->start == -1 || afarm->finish == -1)
		return (0);
	if (afarm->rnum < 3)
		return (0);
	return (1);
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

int		ft_check_rnb(char *line, int i, int j)
{
	char	**arr;

	if (!(arr = ft_strsplit(line, ' ')))
		return (0);
	while (arr[i])
		i++;
	if (i == 3 && arr[0] && ft_isnum(arr[1]) && ft_isnum(arr[2]))
	{
		ft_mapfree(&arr);
		return (1);
	}
	ft_mapfree(&arr);
	i = 0;
	while (line[i])
		if (line[i++] == '-')
			j++;
	if (!(arr = ft_strsplit(line, '-')))
		return (0);
	if (j == 1 && arr[0] && arr[1])
	{
		ft_mapfree(&arr);
		return (-1);
	}
	ft_mapfree(&arr);
	return (0);
}
