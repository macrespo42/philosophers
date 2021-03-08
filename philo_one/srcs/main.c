/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/08 10:14:02 by macrespo         ###   ########.fr       */
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
		pthread_mutex_init(&args->philo->fork, NULL);
		if (args->philo->id % 2 == 1)
			usleep(args->time_to_eat / 10);
		pthread_create(&args->philo->philo_pid, NULL, live, args);
		args->philo = args->philo->next;
		i++;
	}
}

void			*supervisor(void *p_data)
{
	t_args *args;

	args = (t_args*)p_data;
	while (args->philo->next != NULL && args->philo->alive)
	{
		if (args->philo->alive == 0)
			printf("%d is dead\n", args->philo->id);
	}
	return args;
}

int				main(int ac, char **av)
{
	t_args		args;
	t_philo		*head;
	pthread_t	supervisor_t = NULL;

	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		head = init_philos(args);
		args.initial_time = get_tv_msec();
		args.philo = head;
		pthread_create(&supervisor_t, NULL, supervisor, &args);
		init_routine(&args, head);
		pthread_join(supervisor_t, NULL);
		free_philos(head, args);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
