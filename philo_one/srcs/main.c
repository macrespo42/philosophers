/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/01/28 12:31:44 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int     main(int ac, char **av) {
    t_args args;
    timeval current_time;

    if (ac >= 5 && ac < 7)
    {
        if (get_philo_infos(ac, av, &args) == 1)
            return (print_error("Error: bad arguments"));
        gettimeofday(&current_time, NULL);
            // allocate array of philos
            // start threads
            // gerer les fourchettes avec les mutex ???
    }
    else 
        return (print_error("Error: bad numbers of arguments"));
    return (EXIT_SUCCESS);
}