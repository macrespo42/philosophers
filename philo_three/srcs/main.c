/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/21 11:58:57 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		init_routine(t_args *args, t_philo *head)
{
	int		i;
	t_philo	*philo;
	pid_t	philo_pid;

	args->initial_time = get_tv_msec();
	philo = head;
	i = 0;
	philo_pid = 1;
	while (i < args->philos_nb && (philo_pid != 0 && philo_pid != -1))
	{
		philo = philo->next;
		i++;
	}
}

// void			*supervisor(void *p_data)
// {
// 	t_philo		*tmp;
// 	long		now;

// 	tmp = (t_philo*)p_data;
// 	while (tmp->next != NULL && tmp->alive)
// 	{
// 		now = get_tv_msec();
// 		if (tmp->first_meal != 0 &&
// 		now - tmp->last_meal > tmp->args->time_to_die)
// 		{
// 			tmp->alive = 0;
// 			tmp->state = DEAD;
// 			print_state("died", 0, tmp);
// 		}
// 		if (tmp->args->total_meal == tmp->args->philos_nb)
// 		{
// 			tmp->alive = 0;
// 			tmp->state = DEAD;
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (tmp);
// }

int				main(int ac, char **av)
{
	t_philo		philo;
	t_args		args;

	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		philo = init_philos(&args);
		// init_routine(&args, philo);
		free_philos(&philo);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
