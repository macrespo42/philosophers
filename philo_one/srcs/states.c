/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:33:23 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/12 15:16:35 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		print_state(char *action, useconds_t delay, t_philo *philo)
{
	long	timestamp;

	timestamp = get_tv_msec() - philo->args->initial_time;
	printf("[%ld] %d %s\n", timestamp, philo->id, action);
	if (delay > 0)
		usleep(delay * 1000);
}

void		eat(t_philo *philo)
{
	philo->first_meal = 1;
	pthread_mutex_lock(&philo->fork);
	print_state("has taken a fork", 0, philo);
	pthread_mutex_lock(&philo->next->fork);
	print_state("has taken a fork", 0, philo);
	philo->state = EATING;
	print_state("is eating", philo->args->time_to_eat, philo);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	philo->last_meal = get_tv_msec();
	philo->eat_times += 1;
	philo->state = SLEEPING;
}

void		*routine(void *p_data)
{
	t_philo		*philo;

	philo = (t_philo*)p_data;
	if (philo->id % 2 == 0)
		usleep(philo->args->time_to_eat * 1000);
	philo->eat_times = 0;
	philo->last_meal = philo->args->initial_time;
	while (philo->alive)
	{
		eat(philo);
		print_state("is sleeping", philo->args->time_to_sleep, philo);
		philo->state = THINKING;
		print_state("is thinking", 0, philo);
	}
	return (philo);
}
