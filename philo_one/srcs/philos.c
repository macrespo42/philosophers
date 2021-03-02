/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:55:48 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/02 14:48:57 by macrespo         ###   ########.fr       */
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
	t_philo *philo;

	philo = (t_philo*)p_data;
	while (1)
	{
		pthread_mutex_lock(&philo->fork);
		manage_state("has taken a fork", HC_TIME, philo->id);
		pthread_mutex_lock(&philo->next->fork);
		manage_state("has taken a fork", HC_TIME, philo->id);
		philo->state = EATING;
		manage_state("is eating", HC_TIME, philo->id);
		pthread_mutex_unlock(&philo->next->fork);
		pthread_mutex_unlock(&philo->fork);
		philo->state = SLEEPING;
		manage_state("is sleeping", HC_TIME, philo->id);
		usleep(200 * 1000);
		philo->state = THINKING;
		manage_state("is thinking", HC_TIME, philo->id);
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
