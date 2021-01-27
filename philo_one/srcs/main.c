/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:15:12 by macrespo          #+#    #+#             */
/*   Updated: 2021/01/27 09:48:43 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void *myThreadFun(void *vargp) {
    usleep(10);
    (void)vargp;
    printf("Printing from thread !\n");
    return NULL;
}

int main(int ac, char **av) {
    pthread_t thread_id;

    printf("Before thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    /* Parse args */
    if (ac >= 5 && ac < 7) {
        // execute code;
        (void)ac;
        (void)av;
        printf("GOOD\n");
    }
    else 
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}