/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/10 10:59:20 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

// static void		init_routine(t_args *args, t_philo *head)
// {
// 	int		i;
// 	t_philo	*philo;

// 	i = 0;
// 	philo = head;
// 	while (i < args->philos_nb)
// 	{
// 		if (philo->id % 2 == 2)
// 			usleep((args->time_to_eat * 1000) / 10);
// 		pthread_create(&philo->philo_pid, NULL, routine, philo);
// 		pthread_detach(philo->philo_pid);
// 		philo = philo->next;
// 		i++;
// 	}
// }

// void			*supervisor(void *p_data)
// {
// 	t_args *args;

// 	args = (t_args*)p_data;
// 	t_philo *tmp = args->head;
// 	while (tmp->next != NULL && tmp->alive)
// 	{
// 		if (tmp->alive == 0)
// 			printf("%d IS DEAD\n", tmp->id);
// 		tmp = tmp->next;
// 	}
// 	return args;
// }

int				main(int ac, char **av)
{
	// t_philo		*head;
	t_args		args;


	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		head = init_philos(&args);
		// pthread_create(&params.supervisor_pid, NULL, supervisor, &params.args);
		// init_routine(&params.args, params.head);
		// pthread_join(params.supervisor_pid, NULL);
		// free_philos(params.head, params.args);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
