/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:55:48 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/03 15:30:41 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		free_philos(t_philo *head, t_args args)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (i < args.philos_nb)
	{
		tmp = head;
		head = head->next;
		pthread_mutex_destroy(&tmp->fork);
		ft_memdel(tmp);
		i++;
	}
	ft_memdel(head);
}

t_philo		*init_link(int id)
{
	t_philo *link;

	link = malloc(sizeof(t_philo));
	if (!link)
		return (NULL);
	link->id = id;
	link->alive = 1;
	link->state = THINKING;
	link->next = link;
	return (link);
}

t_philo		*init_philos(t_args args)
{
	t_philo	*philo;
	t_philo *new_philo;
	t_philo	*head;
	int		i;

	philo = init_link(0);
	if (!philo)
		return (NULL);
	head = philo;
	i = 1;
	while (i <= args.philos_nb)
	{
		new_philo = init_link(i);
		if (!new_philo)
			return (NULL);
		philo->next = new_philo;
		philo = new_philo;
		i++;
	}
	return (head);
}

void		*live(void *p_data)
{
	t_args		*data;
	t_philo		*philo;
	long		current_time;

	data = (t_args*)p_data;
	philo = (t_philo*)data->philo;
	while (data->all_alive)
	{
		pthread_mutex_lock(&philo->fork);
		manage_state("has taken a fork", 0, philo->id);
		pthread_mutex_lock(&philo->next->fork);
		manage_state("has taken a fork", 0, philo->id);
		philo->state = EATING;
		manage_state("is eating", data->time_to_eat, philo->id);
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
		philo->state = SLEEPING;
		manage_state("is sleeping", data->time_to_sleep, philo->id);
		philo->state = THINKING;
		manage_state("is thinking", 0, philo->id);
		current_time = get_tv_msec();
		if ((current_time - data->initial_time) * 1000 > data->time_to_die)
		{
			printf("current : %ld\n", (current_time));
			printf("TIME TO DIE IN SEC : %d\n", data->time_to_die);
			printf("%d is dead\n", philo->id);
			data->all_alive = 0;
		}
		data->initial_time = get_tv_msec();
	}
	return (philo);
}

void		join_philos(t_philo *philo, t_args args)
{
	int		i;
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
