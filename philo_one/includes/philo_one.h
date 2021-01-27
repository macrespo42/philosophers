#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct s_args {
    int philos_nb;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int time_must_eat;
    int must_eat_nb;
}              t_args;

int			ft_atoi(const char *str);
int         print_error(const char *error_msg);
int         get_philo_infos(int ac, char **av, t_args *args);

#endif
