/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/16 10:58:08 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void		init_forks(t_args *args)
{
	int		i;

	i = 0;
	while (i < args->philos_nb)
	{
		sem_post(args->forks);
		i++;
	}
}

static void		init_routine(t_args *args, t_philo *head)
{
	int		i;
	t_philo	*philo;

	i = 0;
	args->initial_time = get_tv_msec();
	philo = head;
	init_forks(args);
	while (i < args->philos_nb)
	{
		pthread_create(&philo->philo_pid, NULL, routine, philo);
		pthread_detach(philo->philo_pid);
		philo = philo->next;
		i++;
	}
}

void			*supervisor(void *p_data)
{
	t_philo		*tmp;
	long		now;

	tmp = (t_philo*)p_data;
	while (tmp->next != NULL && tmp->alive)
	{
		now = get_tv_msec();
		if (tmp->first_meal != 0 &&
		now - tmp->last_meal > tmp->args->time_to_die)
		{
			tmp->alive = 0;
			tmp->state = DEAD;
			print_state("is dead", 0, tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

int				main(int ac, char **av)
{
	t_philo		*head;
	t_args		args;
	pthread_t	supervisor_pid;

	supervisor_pid = NULL;
	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		head = init_philos(&args);
		pthread_create(&supervisor_pid, NULL, supervisor, head);
		init_routine(&args, head);
		pthread_join(supervisor_pid, NULL);
		free_philos(head, args);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
