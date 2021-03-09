/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:47:52 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/09 13:26:13 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	get_philo_infos(int ac, char **av, t_args *args)
{
	args->philos_nb = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->time_must_eat = 1;
	pthread_mutex_init(&args->printer, NULL);
	if (ac == 6)
		args->time_must_eat = ft_atoi(av[5]);
	if (args->philos_nb <= 0 || args->time_to_die < 0 ||
		args->time_to_eat < 0 || args->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (args->time_must_eat <= 0)
		return (EXIT_FAILURE);
	if (ac < 6)
		args->time_must_eat = -1;
	return (EXIT_SUCCESS);
}
