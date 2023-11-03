/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 03:06:20 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/02 16:17:18 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo, t_world *world)
{
	long long	now;

	now = time_now() - philo->meal_init;
	if (now > philo->world->time_2_die)
	{
		ft_print_status(philo, "died");
		pthread_mutex_unlock(&philo->world->death);
		pthread_mutex_lock(&philo->world->printer);
		pthread_mutex_lock(&philo->world->death);
		world->finish_flag = 1;
		pthread_mutex_unlock(&philo->world->death);
		pthread_mutex_lock(&philo->world->death);
		return (1);
	}
	return (0);
}

int	check_meals(t_philo philo, int last_philo_id)
{
	if (philo.world->max_iter_flag
		&& last_philo_id == philo.world->numbers_philo - 1
		&& philo.iter == philo.world->max_iter)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_world	*world;
	t_philo	*philo;
	int		i;

	i = -1;
	if (init_world(argc, argv, &world))
		return (EXIT_FAILURE);
	philo = malloc(sizeof(t_philo) * world->numbers_philo);
	if (!philo)
		return (error_msj(3), free(world), EXIT_FAILURE);
	while (++i < world->numbers_philo)
	{
		philo[i].id = i + 1;
		philo[i].iter = 0;
		philo[i].meal_init = 0;
		philo[i].world = world;
		philo[i].left_fork = &world->fork[i];
		philo[i].right_fork = 0;
		philo[i].meal_init = time_now();
	}
	if (init_thread(world, philo))
		return (EXIT_FAILURE);
	check_thread(world, philo);
	end_thread(world, philo);
	return (EXIT_SUCCESS);
}
