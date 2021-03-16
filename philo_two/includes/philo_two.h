/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:00:31 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/16 13:06:50 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define SEM_FORKS "forks"
# define SEM_DEATH "printer"

enum				e_state
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct timeval	t_timeval;

typedef struct		s_args {
	int				philos_nb;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_must_eat;
	int				death_flag;
	long			initial_time;
	sem_t			*forks;
	sem_t			*printer;
}					t_args;

typedef struct		s_philo {
	pthread_t		philo_pid;
	int				id;
	int				alive;
	int				eat_times;
	int				first_meal;
	long			last_meal;
	enum e_state	state;
	t_args			*args;
	struct s_philo	*next;
}					t_philo;

int					ft_atoi(const char *str);
int					print_error(const char *error_msg);
int					get_philo_infos(int ac, char **av, t_args *args);
long				get_tv_msec(void);
t_philo				*init_link(int id, t_args *args);
t_philo				*init_philos(t_args *args);
void				free_philos(t_philo *head, t_args args);
void				ft_memdel(void *ptr);
void				ft_msleep(int milliseconds);
void				*routine(void *p_data);
void				print_state(char *action, useconds_t delay, t_philo *philo);

#endif
