/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:59:12 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/02 16:02:09 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_now(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == 0)
		return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	else
		return (-1);
}

void	ft_usleep(long long time)
{
	long long	init_time;

	init_time = time_now();
	while ((time_now() - init_time) < time)
		usleep(150);
}

void	ft_print_status(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->world->printer);
	printf("%lld %i %s\n", (time_now() - p->world->time), p->id, str);
	pthread_mutex_unlock(&p->world->printer);
}

int	check_if_all_numbers(char *num)
{
	int	n;

	n = 0;
	while (num[n])
	{
		if (!(num[n] >= '0' && num[n] <= '9'))
			return (1);
		n++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	if (check_if_all_numbers(str))
		return (-1);
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i] != '\0')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (str[i] - '0') + (num * 10);
		i++;
	}
	return (num * sign);
}
