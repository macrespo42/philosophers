/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:33:23 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/10 13:01:27 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		manage_state(char *action, useconds_t delay, t_philo *philo)
{
	// long	timestamp;

	// pthread_mutex_lock(&data->printer);
	// timestamp = data->philo->last_meal - data->initial_time;
	printf("%d %s\n", philo->id, action);
	if (delay > 0)
		usleep(delay * 1000);
	// pthread_mutex_unlock(&data->printer);
}

// void		eat(t_args *data)
// {
// 	pthread_mutex_lock(&data->philo->fork);
// 	manage_state("has taken a fork", 0, data->philo->id);
// 	pthread_mutex_lock(&data->philo->next->fork);
// 	manage_state("has taken a fork", 0, data->philo->id);
// 	data->philo->state = EATING;
// 	manage_state("is eating", data->time_to_eat, data->philo->id);
// 	pthread_mutex_unlock(&data->philo->next->fork);
// 	pthread_mutex_unlock(&data->philo->fork);
//     data->philo->state = SLEEPING;
// }

void		*routine(void *p_data)
{
	t_philo		*philo;

	philo = (t_philo*)p_data;
	printf("LAUNCH ROUTINE FOR THREAD : %d\n", philo->id);
	while (philo->alive) {
		// eat(data);
		manage_state("is eating", philo->args->time_to_eat, philo);
		manage_state("is sleeping", philo->args->time_to_sleep, philo);
		manage_state("is thinking", 0, philo);
	}
	return (philo);
}
