/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:54:46 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/02 16:03:59 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_thread(t_world *world, t_philo *philo)
{
	int	i;

	i = 0;
	world->time = time_now();
	while (i < world->numbers_philo)
	{
		philo[i].right_fork = philo[(i + 1) % world->numbers_philo].left_fork;
		if (pthread_create(&philo[i].thread_id, NULL, &thread_function,
				&philo[i]) != 0)
			return (error_msj(6), EXIT_FAILURE);
		i++;
	}
	pthread_mutex_lock(&philo->world->ready_mutex);
	world->ready = 1;
	world->time = time_now();
	pthread_mutex_unlock(&philo->world->ready_mutex);
	return (0);
}

void	*thread_function(void *work)
{
	t_philo	*philo;

	philo = (t_philo *)work;
	pthread_mutex_lock(&philo->world->ready_mutex);
	while (!philo->world->ready)
	{
		pthread_mutex_unlock(&philo->world->ready_mutex);
		usleep(10);
		pthread_mutex_lock(&philo->world->ready_mutex);
	}
	pthread_mutex_unlock(&philo->world->ready_mutex);
	if (philo->id & 1)
		ft_usleep(philo->world->time_2_eat / 2);
	pthread_mutex_lock(&philo->world->death);
	while (!philo->world->finish_flag)
		eat_sleep_think(philo);
	pthread_mutex_unlock(&philo->world->death);
	return (NULL);
}

void	eat_sleep_think(t_philo *philo)
{
	pthread_mutex_unlock(&philo->world->death);
	pthread_mutex_lock(philo->left_fork);
	ft_print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	ft_print_status(philo, "has taken a fork");
	ft_print_status(philo, "is eating");
	ft_usleep((philo->world->time_2_eat));
	pthread_mutex_lock(&philo->world->death);
	philo->meal_init = time_now();
	pthread_mutex_unlock(&philo->world->death);
	philo->iter++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	ft_print_status(philo, "is sleeping");
	ft_usleep((philo->world->time_2_sleep));
	ft_print_status(philo, "is thinking");
	pthread_mutex_lock(&philo->world->death);
}

int	check_thread(t_world *world, t_philo *philo)
{
	int	i;

	i = -1;
	while (!world->ready)
		continue ;
	while (!world->finish_flag)
	{
		i = (i + 1) % world->numbers_philo;
		pthread_mutex_lock(&philo->world->death);
		if (check_death(&philo[i], world))
			return (printf("Game over :( \n"), 1);
		if (check_meals(philo[i], i))
		{
			world->finish_flag = 1;
			pthread_mutex_lock(&philo->world->printer);
			return (printf("ALL PHILOSOPHERS HAVE EATEN :) \n"), 1);
		}
		pthread_mutex_unlock(&philo->world->death);
	}
	return (0);
}
