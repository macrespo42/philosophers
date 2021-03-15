/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:47:52 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/15 14:59:51 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int	get_philo_infos(int ac, char **av, t_args *args)
{
	args->philos_nb = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->time_must_eat = 1;
	args->death_flag = 0;
	args->printer = malloc(sizeof(sem_t));
	args->forks = malloc(sizeof(sem_t));
	if (!args->printer || !args->forks)
		return (EXIT_FAILURE);
	args->forks = sem_open(SEM_NAME, O_CREAT);
	args->printer = sem_open(SEM_NAME, O_CREAT);
	sem_post(args->printer);
	if (ac == 6)
		args->time_must_eat = ft_atoi(av[5]);
	if (args->philos_nb <= 1 || args->time_to_die < 0 ||
		args->time_to_eat < 0 || args->time_to_sleep < 0)
		return (EXIT_FAILURE);
	if (args->time_must_eat <= 0)
		return (EXIT_FAILURE);
	if (ac < 6)
		args->time_must_eat = -1;
	return (EXIT_SUCCESS);
}
