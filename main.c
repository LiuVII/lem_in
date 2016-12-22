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

int	main(int argc, char const **argv)
{
	t_graph afarm;
	// int		i;

	if (argc < 1 || !argv[0])
		return (0);
	ft_farm_init(&afarm);
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
