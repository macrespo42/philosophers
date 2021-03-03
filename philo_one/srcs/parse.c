/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:47:52 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/03 13:20:33 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int	get_philo_infos(int ac, char **av, t_args *args)
{
	args->philos_nb = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->all_alive = 1;
	if (ac == 6)
	{
		args->must_eat_defined = 1;
		args->time_must_eat = ft_atoi(av[5]);
	}
	else
		args->must_eat_defined = 0;
	if (args->philos_nb <= 0 || args->time_to_die < 0 ||
		args->time_to_eat < 0 || args->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (args->must_eat_defined == 1 && args->time_must_eat <= 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
