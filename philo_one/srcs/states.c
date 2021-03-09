/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:33:23 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/09 14:23:49 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		manage_state(char *action, useconds_t delay, t_args *data)
{
	long	timestamp;

	pthread_mutex_lock(&data->printer);
	timestamp = data->philo->last_meal - data->initial_time;
	printf("%ld %d %s\n", timestamp, data->philo->id, action);
	if (delay > 0)
		usleep(delay * 1000);
	pthread_mutex_unlock(&data->printer);
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
	t_args		*data;

	data = (t_args*)p_data;
	printf("LAUNCH ROUTINE FOR THREAD : %d\n", data->philo->id);
	data->initial_time = get_tv_msec();
	data->philo->last_meal = data->initial_time;
	while (data->philo->alive) {
		// eat(data);
		manage_state("is eating", data->time_to_eat, data);
		data->philo->last_meal = get_tv_msec();
		manage_state("is sleeping", data->time_to_sleep, data);
		data->philo->last_meal = get_tv_msec();
		manage_state("is thinking", 0, data);
		data->philo->last_meal = get_tv_msec();
	}
	return (data->philo);
}
