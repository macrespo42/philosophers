/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:33:23 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/11 11:56:20 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		manage_state(char *action, useconds_t delay, t_philo *philo)
{
	long	timestamp;

	timestamp = philo->last_meal - philo->args->initial_time;
	printf("[%ld] %d %s\n",timestamp, philo->id, action);
	if (delay > 0)
		usleep(delay * 1000);
	philo->last_meal = get_tv_msec();
}

void		eat(t_philo *philo)
{
	philo->first_meal = 1;
	pthread_mutex_lock(&philo->fork);
	manage_state("has taken a fork", 0, philo);
	pthread_mutex_lock(&philo->next->fork);
	manage_state("has taken a fork", 0, philo);
	philo->state = EATING;
	manage_state("is eating", philo->args->time_to_eat, philo);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	philo->last_meal = get_tv_msec();
    philo->state = SLEEPING;
}

void		*routine(void *p_data)
{
	t_philo		*philo;

	philo = (t_philo*)p_data;
	if (philo->id % 2 == 1)
			usleep(philo->args->time_to_eat * 1000);
	philo->last_meal = philo->args->initial_time;
	while (philo->alive) {
		eat(philo);
		manage_state("is sleeping", philo->args->time_to_sleep, philo);
		philo->state = THINKING;
		manage_state("is thinking", 0, philo);
	}
	return (philo);
}
