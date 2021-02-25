/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/02/25 15:50:00 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		init_philos(t_args args)
{
	t_philo		**philos;
	int			i;

	philos = malloc(sizeof(t_philo*) * args.philos_nb);
	if (!philos)
		return (EXIT_FAILURE);
	i = 0;
	while (i < args.philos_nb)
	{
		i += 2;
	}
	i = 1;
	while (i < args.philos_nb)
	{
		i += 2;
	}
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	t_args		args;
	t_timeval	current_time;

	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		gettimeofday(&current_time, NULL);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
