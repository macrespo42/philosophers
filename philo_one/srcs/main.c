/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/09 14:21:26 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		init_routine(t_args *args, t_philo *head)
{
	int		i;

	i = 0;
	args->philo = head;
	while (i < args->philos_nb)
	{
		if (args->philo->id % 2 == 2)
			usleep((args->time_to_eat * 1000) / 10);
		pthread_create(&args->philo->philo_pid, NULL, routine, args);
		pthread_detach(args->philo->philo_pid);
		args->philo = args->philo->next;
		i++;
	}
}

void			*supervisor(void *p_data)
{
	t_args *args;

	args = (t_args*)p_data;
	t_philo *tmp = args->philo;
	while (tmp->next != NULL && tmp->alive)
	{
		if (tmp->alive == 0)
			printf("jnfief");
		tmp = tmp->next;
	}
	return args;
}

int				main(int ac, char **av)
{
	t_args		args;
	t_philo		*head;
	pthread_t	supervisor_pid;

	supervisor_pid = NULL;
	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		head = init_philos(args);
		pthread_create(&supervisor_pid, NULL, supervisor, &args);
		init_routine(&args, head);
		pthread_join(supervisor_pid, NULL);
		free_philos(head, args);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
