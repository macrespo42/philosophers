/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:33:23 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/08 15:27:52 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		manage_state(char *action, useconds_t delay, int philo_id)
{
	printf("%d %s\n", philo_id, action);
	if (delay > 0)
		usleep(delay * 1000);
}

void		eat(t_args *data)
{
	pthread_mutex_lock(&data->philo->fork);
	manage_state("has taken a fork", 0, data->philo->id);
	pthread_mutex_lock(&data->philo->next->fork);
	manage_state("has taken a fork", 0, data->philo->id);
	data->philo->state = EATING;
	manage_state("is eating", data->time_to_eat, data->philo->id);
	pthread_mutex_unlock(&data->philo->next->fork);
	pthread_mutex_unlock(&data->philo->fork);
    data->philo->state = SLEEPING;
}

void		*routine(void *p_data)
{
	t_args		*data;

	data = (t_args*)p_data;
	data->initial_time = get_tv_msec();
	while (data->philo->alive) {
		eat(data);
		manage_state("is sleeping", data->time_to_sleep, data->philo->id);
    	data->philo->state = THINKING;
		manage_state("is thinking", 0, data->philo->id);
		data->philo->last_meal = get_tv_msec();
	}
	return (data->philo);
}
