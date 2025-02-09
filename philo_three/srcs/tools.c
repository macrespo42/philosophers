/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 14:49:07 by macrespo          #+#    #+#             */
/*   Updated: 2021/03/19 14:21:32 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		neg;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] ==
	'\v' || str[i] == '\f' || str[i] == ' ')
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

void		ft_memdel(void *ptr)
{
	if (ptr)
		free(ptr);
	ptr = NULL;
}

long		get_tv_msec(void)
{
	t_timeval timestamp;

	gettimeofday(&timestamp, NULL);
	return ((timestamp.tv_sec * 1000) + (timestamp.tv_usec / 1000));
}

void		ft_msleep(int milliseconds)
{
	long	time;

	time = get_tv_msec();
	while (get_tv_msec() < time + milliseconds)
		usleep(milliseconds);
}
