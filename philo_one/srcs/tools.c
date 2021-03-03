/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:49:07 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/03 15:30:33 by macrespo         ###   ########.fr       */
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

void		manage_state(char *action, useconds_t delay, int philo_id)
{
	printf("%d %s\n", philo_id, action);
	if (delay > 0)
		usleep(delay * 1000);
}

void		ft_memdel(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

long		get_tv_msec(void)
{
	t_timeval timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}