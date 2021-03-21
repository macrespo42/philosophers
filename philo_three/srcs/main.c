/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/21 14:12:53 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		init_routine(t_args *args, t_philo *philo)
{
	int		i;
	pid_t	*pids;

	pids = malloc(sizeof(pid_t) * args->philos_nb);
	if (!pids)
		return ;
	args->initial_time = get_tv_msec();
	pids[0] = 1;
	i = 0;
	while (pids[i] != 0 && i++ < args->philos_nb)
	{
		pids[i] = fork();
		philo->id = i;
		if (pids[i] == 0)
			routine(philo);
	}
	waitpid(-1, NULL, 0);
	// i = 0;
	// while (i++ < args->philos_nb)
	// 	kill(pids[i], SIGKILL);
	// ft_memdel(pids);
}

int				main(int ac, char **av)
{
	t_philo		philo;
	t_args		args;

	if (ac >= 5 && ac < 7)
	{
		if (get_philo_infos(ac, av, &args) == 1)
			return (print_error("Error: bad arguments"));
		philo = init_philos(&args);
		init_routine(&args, &philo);
		free_philos(&philo);
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
