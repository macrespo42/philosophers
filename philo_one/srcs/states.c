/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:33:23 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/08 09:53:24 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		manage_state(char *action, useconds_t delay, int philo_id)
{
	printf("%d %s\n", philo_id, action);
	if (delay > 0)
		usleep(delay * 1000);
}

void        check_vital(long current_time, t_philo *philo, t_args *data)
{
    current_time = get_tv_msec();
    if ((current_time - data->initial_time) > data->time_to_die)
		{
			printf("current - initial : %ld\n", (current_time - data->initial_time));
			printf("TIME TO DIE IN SEC : %d\n", data->time_to_die);
			printf("%d is dead\n", philo->id);
            philo->alive = 0;
	}
    data->initial_time = get_tv_msec();
}

int         eat(t_args *data, t_philo *philo, long current_time)
{
	pthread_mutex_lock(&philo->fork);
	manage_state("has taken a fork", 0, philo->id);
	pthread_mutex_lock(&philo->next->fork);
	manage_state("has taken a fork", 0, philo->id);
	philo->state = EATING;
	manage_state("is eating", data->time_to_eat, philo->id);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
    check_vital(current_time, philo, data);
    philo->state = SLEEPING;
    return 1;
}

void		*live(void *p_data)
{
	t_args		*data;
	t_philo		*philo;
	long		current_time;

    current_time = 0;
	data = (t_args*)p_data;
	philo = (t_philo*)data->philo;
	while (philo->alive)
	{
        if (philo->state == EATING)
            eat(data, philo, current_time);
        if (philo->state == SLEEPING)
        {
		    philo->state = SLEEPING;
		    manage_state("is sleeping", data->time_to_sleep, philo->id);
            check_vital(current_time, philo, data);
            philo->state = THINKING;
        }
        if (philo->state == THINKING)
        {
            philo->state = THINKING;
		    manage_state("is thinking", 0, philo->id);
            check_vital(current_time, philo, data);
            philo->state = EATING;
        }
	}
	return (philo);
}
