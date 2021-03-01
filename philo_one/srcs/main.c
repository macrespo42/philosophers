/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/01 16:15:54 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*live(void *p_data)
{
	t_philo *philo;

	philo = (t_philo*)p_data;
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		printf("%d has taken a fork\n", philo->id);
		pthread_mutex_lock(&philo->next->fork);
		printf("%d has taken a second fork\n");
		philo->state = EATING;
		printf("%d is eating\n", philo->id);
		usleep(200 * 1000);
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
		philo->state = SLEEPING;
		printf("%d is sleeping\n", philo->id);
		usleep(200 * 1000);
		philo->state = THINKING;
		printf("%d is thinking\n", philo->id);
	}
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
