/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/02/25 16:08:58 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo	*init_link(int id)
{
	t_philo *link;

	link->id = id;
	link->alive = 1;
	link->state = THINKING;
	link->next = link;
}

t_philo	*init_philos(t_args args)
{
	t_philo	*philo;
	t_philo *new_philo;
	t_philo	*head;
	int		i;

	philo = init_link(0);
	head = philo;
	i = 1;
	while (i < args.philos_nb)
	{
		new_philo = init_link(i);
		philo->next = new_philo;
		philo = new_philo;
		i++;
	}
	return (head);
}

int		main(int ac, char **av)
{
	t_args		args;
	t_timeval	current_time;
	t_philo		*head;

	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		gettimeofday(&current_time, NULL);
		head = init_philos(args);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
