/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/02 14:15:00 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		main(int ac, char **av)
{
	t_args		args;
	t_timeval	current_time;
	t_philo		*head;
	t_philo		*philos;

	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		gettimeofday(&current_time, NULL);
		head = init_philos(args);
		int i;
		
		i = 0;
		philos = head;
		while (i < args.philos_nb)
		{
			pthread_mutex_init(&philos->fork, NULL);
			if (philos->id % 2 != 0)
				usleep(50 * 1000);
			pthread_create(&philos->philo_pid, NULL, live, philos);
			philos = philos->next;
			i++;
		}
		join_philos(head, args);
		free_philos(head, args);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
