/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 13:55:48 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/22 10:59:27 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void		free_philos(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_DEATH);
	sem_unlink(SEM_MEAL);
}

t_philo		init_philos(t_args *args)
{
	t_philo philo;

	philo.id = 0;
	philo.alive = 1;
	philo.state = THINKING;
	philo.args = args;
	philo.first_meal = 0;
	philo.eat_times = 0;
	philo.total_meal = 0;
	return (philo);
}
