/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:32:21 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/02 16:02:35 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_world *world)
{
	int	i;

	i = -1;
	world->fork = malloc(sizeof(pthread_mutex_t) * world->numbers_philo);
	if (!world->fork)
		return (error_msj(3), -1);
	while (++i < world->numbers_philo)
		if (pthread_mutex_init(&world->fork[i], NULL) == -1)
			return (error_msj(5), -1);
	if (pthread_mutex_init(&world->death, NULL) == -1)
		return (error_msj(5), -1);
	if (pthread_mutex_init(&world->printer, NULL) == -1)
		return (error_msj(5), -1);
	if (pthread_mutex_init(&world->data_saver, NULL) == -1)
		return (error_msj(5), -1);
	if (pthread_mutex_init(&world->ready_mutex, NULL) == -1)
		return (error_msj(5), -1);
	return (0);
}

int	check_param(int ac, char **av, t_world *world)
{
	if (ac != 5 && ac != 6)
		return (error_msj(1), EXIT_FAILURE);
	world->numbers_philo = ft_atoi(av[1]);
	world->time_2_die = ft_atoi(av[2]);
	world->time_2_eat = ft_atoi(av[3]);
	world->time_2_sleep = ft_atoi(av[4]);
	world->max_iter_flag = 0;
	world->ready = 0;
	if (ac == 6)
	{
		world->max_iter = ft_atoi(av[5]);
		world->max_iter_flag = 1;
		if (world->max_iter <= 0)
			return (error_msj(2), EXIT_FAILURE);
	}
	if (world->numbers_philo <= 0 || world->time_2_die <= 0
		|| world->time_2_eat <= 0 || world->time_2_sleep <= 0)
		return (error_msj(2), EXIT_FAILURE);
	return (0);
}

int	init_world(int argc, char **argv, t_world **world)
{
	int	i;

	i = -1;
	*world = malloc(sizeof(t_world));
	if (!*world)
		return (error_msj(3), EXIT_FAILURE);
	if (check_param(argc, argv, *world) == EXIT_FAILURE)
		return (free(*world), EXIT_FAILURE);
	if (init_mutex(*world) == -1)
		return (free(*world), EXIT_FAILURE);
	return (0);
}
