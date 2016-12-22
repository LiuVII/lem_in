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

int	ft_parse_flags(const char **flags, t_graph *afarm)
{
	int i;

	i = 0;
	while (flags[i])
	{
		if (!ft_strcmp(flags[i], "-s"))
			afarm->spine[0] = 1;
		else if (!ft_strcmp(flags[i], "-p"))
			afarm->spine[1] = 1;
		else if (!ft_strcmp(flags[i], "-i"))
			afarm->spine[2] = 1;
		else if (!ft_strcmp(flags[i], "-n"))
			afarm->spine[3] = 1;
		else if (!ft_strcmp(flags[i], "-e"))
			afarm->spine[4] = 1;
		else
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char const **argv)
{
	t_graph afarm;

	if (argc < 1 || !argv[0])
		return (0);
	ft_farm_init(&afarm);
	if (argc > 1 && ft_parse_flags(&(argv[1]), &afarm))
		ft_free_n_exit(NULL, NULL, -1);
	ft_read(&afarm, NULL, -1, -1);
	afarm.q = (int*)malloc(sizeof(int) * afarm.rnum);
	afarm.s = (int*)malloc(sizeof(int) * afarm.rnum);
	afarm.aq = (int*)malloc(sizeof(int) * afarm.anum);
	afarm.as = (int*)malloc(sizeof(int) * afarm.anum);
	ft_print_farm(&afarm, -1, -1);
	ft_solve_farm(&afarm);
	ft_clear_farm(&afarm);
	return (0);
}
