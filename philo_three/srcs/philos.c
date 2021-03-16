/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:55:48 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/16 11:02:58 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		free_philos(t_philo *head, t_args args)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	while (i < args.philos_nb - 1)
	{
		tmp = head;
		head = head->next;
		ft_memdel(tmp);
		i++;
	}
	sem_close(args.forks);
	sem_close(args.printer);
	ft_memdel(head);
}

t_philo		*init_link(int id, t_args *arg)
{
	t_philo *link;

	link = malloc(sizeof(t_philo));
	if (!link)
		return (NULL);
	link->id = id;
	link->alive = 1;
	link->state = THINKING;
	link->args = arg;
	link->first_meal = 0;
	link->eat_times = 0;
	link->next = link;
	return (link);
}

t_philo		*init_philos(t_args *args)
{
	t_philo	*philo;
	t_philo *new_philo;
	t_philo	*head;
	int		i;

	philo = init_link(1, args);
	if (!philo)
		return (NULL);
	head = philo;
	i = 1;
	while (i <= args->philos_nb - 1)
	{
		i++;
		new_philo = init_link(i, args);
		if (!new_philo)
			return (NULL);
		philo->next = new_philo;
		philo = new_philo;
	}
	philo->next = head;
	return (head);
}
