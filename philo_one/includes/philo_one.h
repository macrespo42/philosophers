/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:31 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/08 09:20:21 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define FALSE 0
# define TRUE 1

enum				e_state
{
	EATING,
	SLEEPING,
	THINKING
};

typedef struct timeval	t_timeval;

typedef struct		s_philo {
	pthread_t		philo_pid;
	pthread_mutex_t	fork;
	int				id;
	int				alive;
	enum e_state	state;
	struct s_philo	*next;
}					t_philo;

typedef struct		s_args {
	int				philos_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	int				must_eat_defined;
	int				all_alive;
	long			initial_time;
	t_philo			*philo;
}					t_args;

int					ft_atoi(const char *str);
int					print_error(const char *error_msg);
int					get_philo_infos(int ac, char **av, t_args *args);
long				get_tv_msec(void);
t_philo				*init_link(int id);
t_philo				*init_philos(t_args args);
void				free_philos(t_philo *head, t_args args);
void				ft_memdel(void *ptr);
void				*live(void *p_data);
void				manage_state(char *action, useconds_t delay, int philo_id);

#endif
