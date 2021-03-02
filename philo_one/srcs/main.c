/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/02 15:41:06 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		init_routine(t_args *args, t_philo *head)
{
	int		i;

	i = 0;
	args->philo = head;
	while (i < args->philos_nb)
	{
		pthread_mutex_init(&args->philo->fork, NULL);
		if (args->philo->id % 2 != 0)
			usleep((args->time_to_eat * 0.9) * 1000);
		pthread_create(&args->philo->philo_pid, NULL, live, args);
		args->philo = args->philo->next;
		i++;
	}
}

int				main(int ac, char **av)
{
	t_args		args;
	t_timeval	current_time;
	t_philo		*head;

	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		gettimeofday(&current_time, NULL);
		head = init_philos(args);
		init_routine(&args, head);
		join_philos(head, args);
		free_philos(head, args);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
