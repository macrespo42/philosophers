/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/01 15:35:02 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*live(void *p_data)
{
	t_philo *philo;

	philo = (t_philo*)p_data;
	printf("I'm the thread nb : %d\n", philo->id);
	pthread_mutex_lock(&philo->fork);
	philo->state = EATING;
	pthread_mutex_unlock(&philo->fork);
	philo->state = SLEEPING;
	usleep(10);
	philo->state = THINKING;
	return (philo);
}

void join_philos(t_philo *philo, t_args args)
{
	int i;
	t_philo *tmp;

	tmp = philo;
	i = 0;
	while (i < args.philos_nb)
	{
		pthread_join(tmp->philo_pid, NULL);
		tmp = tmp->next;
		i++;
	}
}

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
