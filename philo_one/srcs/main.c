/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/01/27 15:02:08 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int     main(int ac, char **av) {
    t_args args;

    if (ac >= 5 && ac < 7)
    {
        if (get_philo_infos(ac, av, &args) == 1)
            return (print_error("Error: bad arguments"));
    }
    else 
        return (print_error("Error: bad numbers of arguments"));
    return (EXIT_SUCCESS);
}