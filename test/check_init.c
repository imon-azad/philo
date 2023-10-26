/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:32:21 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/26 18:32:06 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_param(int ac, char **av, t_param *data)
{
	if (ac != 5 && ac != 6)
		return (error_msj(1), EXIT_FAILURE);
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->meal_flag = 0;
	data->ready = 0;
    data->time = time_now();
	data->finish_flag = 0;
	if (ac == 6)
	{
		data->n_time_eat = ft_atoi(av[5]);
		data->meal_flag = 1;
		if (data->n_time_eat <= 0)
			return (error_msj(2), EXIT_FAILURE);
	}
	if (data->n_philo <= 0 || data->t_die <= 0 || data->t_eat <= 0
		|| data->t_sleep <= 0)
		return (error_msj(2), EXIT_FAILURE);
	if (data->n_philo)
		if (init_mutex(data) == -1)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	init_mutex(t_param *data)
{
	int	i;

	i = -1;
	data->fork = 0;
	data->death = 0;
	data->printer = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->fork)
		return (error_msj(3), -1);
	while (++i < data->n_philo)
		if (pthread_mutex_init(&data->fork[i], NULL) == -1)
			return (error_msj(5), -1);
	data->death = malloc(sizeof(pthread_mutex_t));
	if (!data->death)
		return (error_msj(3), -1);
	if (pthread_mutex_init(data->death, NULL) == -1)
		return (error_msj(5), -1);
	data->printer = malloc(sizeof(pthread_mutex_t));
	if (!data->printer)
		return (error_msj(3), -1);
	if (pthread_mutex_init(data->printer, NULL) == -1)
		return (error_msj(5), -1);
	return (0);
}
