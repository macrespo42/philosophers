/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:49:07 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/02 14:49:56 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		neg;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v'
	|| str[i] == '\f' || str[i] == ' ')
		i++;
	neg = 1;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	res = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * neg);
}

void		manage_state(char *action, useconds_t action_delay, int philo_id)
{
	printf("%d %s\n", philo_id, action);
	if (action_delay > 0)
		usleep(action_delay * 1000);
}

void		ft_memdel(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
