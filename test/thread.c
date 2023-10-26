/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:44:53 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/26 17:09:23 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_thread(t_param *data, t_philo *philo)
{
	int	i;

	data->time = time_now();
	i = 0;
	while (i < data->n_philo)
	{
		philo[i].right_fork = philo[(i + 1) % data->n_philo].left_fork;
		if (pthread_create(&philo->thread_id, NULL, &thread_function,
				&philo[i]) != 0)
			return (error_msj(6), EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		philo[i].meal_init = data->time;
		i++;
	}
	data->ready = 1;
	return (0);
}

void	*thread_function(void *work)
{
	t_philo	*philo;

	philo = (t_philo *)work;
	while (!philo->param->ready)
		continue ;
	if (philo->id & 1)
		ft_usleep(philo->param->t_eat);
	while (!philo->param->finish_flag)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		ft_print_status(philo, "has taken a fork");
		ft_print_status(philo, "is eating");
		philo->meal_init = time_now();
		ft_usleep((philo->param->t_eat));
		philo->iter++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		ft_print_status(philo, "is sleeping");
		ft_usleep((philo->param->t_sleep));
		ft_print_status(philo, "is thinking");
	}
	return (NULL);
}

int	check_thread(t_param *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (!data->ready)
		continue ;
	while (!data->finish_flag)
	{
		while (i < data->n_philo)
		{
			if (check_death(&philo[i]))
			{
				data->finish_flag = 1;
				return (printf("Game over :( \n"), 1);
			}
			if (check_meals(philo[i], i))
			{
				data->finish_flag = 1;
				ft_usleep(1 * data->n_philo);
				return (printf("ALL PHILOSOPHERS HAVE EATEN :) \n"), 1);
			}
			i++;
		}
		i = 0;
	}
	return (0);
}

int	check_death(t_philo *philo)
{
	long int	now;

	pthread_mutex_lock(philo->param->death);
	now = time_now() - philo->meal_init;
	if (now >= philo->param->t_die)
	{
		pthread_mutex_unlock(philo->param->death);
		philo->param->finish_flag = 1;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (ft_print_status(philo, "died"), 1);
	}
	pthread_mutex_unlock(philo->param->death);
	return (0);
}

int	check_meals(t_philo philo, int last_philo_id)
{
	if (philo.param->meal_flag && last_philo_id == philo.param->n_philo - 1
		&& philo.iter == philo.param->n_time_eat)
		return (1);
	return (0);
}
