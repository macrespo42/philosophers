/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:33:23 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/16 13:53:27 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		print_state(char *action, useconds_t delay, t_philo *philo)
{
	long	timestamp;

	timestamp = get_tv_msec() - philo->args->initial_time;
	pthread_mutex_lock(philo->args->printer);
	if (!philo->args->death_flag)
		printf("[%ld] %d %s\n", timestamp, philo->id, action);
	pthread_mutex_unlock(philo->args->printer);
	if (philo->state == DEAD)
		philo->args->death_flag = 1;
	if (delay > 0)
		ft_msleep(delay);
}

void		eat(t_philo *philo)
{
	philo->first_meal = 1;
	pthread_mutex_lock(&philo->fork);
	print_state("has taken a fork", 0, philo);
	pthread_mutex_lock(&philo->next->fork);
	print_state("has taken a fork", 0, philo);
	philo->state = EATING;
	philo->last_meal = get_tv_msec();
	print_state("is eating", philo->args->time_to_eat, philo);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
	philo->state = SLEEPING;
}

void		*routine(void *p_data)
{
	t_philo		*philo;

	philo = (t_philo*)p_data;
	if (philo->id % 2 == 0)
		ft_msleep(philo->args->time_to_eat);
	philo->last_meal = get_tv_msec();
	while (philo->alive && (philo->args->time_must_eat == -1
	|| (philo->args->time_must_eat != -1
	&& philo->eat_times < philo->args->time_must_eat)))
	{
		eat(philo);
		philo->eat_times += 1;
		print_state("is sleeping", philo->args->time_to_sleep, philo);
		philo->state = THINKING;
		print_state("is thinking", 0, philo);
	}
	return (philo);
}
