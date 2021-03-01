/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/01 10:40:50 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*live(void *p_data)
{
	t_philo *philo;

	philo = (t_philo*)p_data;
	printf("I'm the thread nb : %d\n", philo->id);
	pthread_mutex_lock(&philo->fork);
	//feed the philo
	pthread_mutex_unlock(&philo->fork);
	return (philo);
}

int		main(int ac, char **av)
{
	t_args		args;
	t_timeval	current_time;
	t_philo		*head;
	t_philo *philos;

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
			if (i % 0 != 0)
				usleep(50);
			pthread_mutex_init(&philos->fork, NULL);
			pthread_create(&philos->philo_pid, NULL, live, philos);
			philos = philos->next;
			i++;
		}
		free_philos(head, args);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	usleep(5000);
	return (EXIT_SUCCESS);
}
