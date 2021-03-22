/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/22 11:48:12 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		*meal_supervisor(void *arg)
{
	int		i;
	t_args	*args;

	args = (t_args*)arg;
	i = 0;
	while (i < args->time_must_eat)
	{
		sem_wait(args->meals);
		i++;
	}
	i = 0;
	while (i++ < args->philos_nb)
		kill(args->pids[i], SIGTERM);
	ft_memdel(args->pids);
	free_philos();
	exit(0);
	return (args);
}

void		init_routine(t_args *args, t_philo *philo)
{
	int			i;
	pthread_t	meal_pid;

	args->pids = malloc(sizeof(pid_t) * args->philos_nb);
	if (!args->pids)
		return ;
	args->initial_time = get_tv_msec();
	args->pids[0] = 1;
	i = 0;
	while (args->pids[i] != 0 && i++ < args->philos_nb)
	{
		args->pids[i] = fork();
		philo->id = i;
		if (args->pids[i] == 0)
			routine(philo);
	}
	if (args->time_must_eat != -1)
		pthread_create(&meal_pid, NULL, meal_supervisor, args);
	waitpid(-1, NULL, 0);
	i = 0;
	while (i++ < args->philos_nb)
		kill(args->pids[i], SIGKILL);
	ft_memdel(args->pids);
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
		free_philos();
	}
	else
		return (print_error("Error: bad numbers of arguments"));
	return (EXIT_SUCCESS);
}
