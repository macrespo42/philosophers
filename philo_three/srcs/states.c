/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:33:23 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/16 11:02:58 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		print_state(char *action, useconds_t delay, t_philo *philo)
{
	long	timestamp;

	sem_wait(philo->args->printer);
	timestamp = get_tv_msec() - philo->args->initial_time;
	if (!philo->args->death_flag)
		printf("[%ld] %d %s\n", timestamp, philo->id, action);
	if (philo->state == DEAD)
		philo->args->death_flag = 1;
	sem_post(philo->args->printer);
	if (delay > 0)
		ft_msleep(delay);
}

void		eat(t_philo *philo)
{
	philo->first_meal = 1;
	sem_wait(philo->args->forks);
	print_state("has taken a fork", 0, philo);
	sem_wait(philo->args->forks);
	print_state("has taken a fork", 0, philo);
	philo->state = EATING;
	print_state("is eating", philo->args->time_to_eat, philo);
	sem_post(philo->args->forks);
	sem_post(philo->args->forks);
	philo->last_meal = get_tv_msec();
	philo->state = SLEEPING;
}

void		*routine(void *p_data)
{
	t_philo		*philo;

	philo = (t_philo*)p_data;
	if (philo->id % 2 == 0)
		ft_msleep(philo->args->time_to_eat);
	philo->last_meal = philo->args->initial_time;
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