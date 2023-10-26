/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:57:24 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/26 17:47:48 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_now(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == 0)
		return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
	else
		return (EXIT_FAILURE);
}

void	ft_print_status(t_philo *p, char *str)
{
	if (!p->param->finish_flag || ft_strncmp(str, "died", 4) == 0)
	{
		pthread_mutex_lock(p->param->printer);
		printf("%li %i %s\n", (time_now() - p->param->time), p->id, str);
		pthread_mutex_unlock(p->param->printer);
	}
}

void	ft_usleep(long int time)
{
	long int	init_time;

	init_time = time_now();
	while ((time_now() - init_time) < time)
		usleep(150);
}

int	main(int argc, char **argv)
{
	t_param	data;
	t_philo	*philo;
	int		i;

	i = -1;
	if (check_param(argc, argv, &data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	philo = malloc(sizeof(t_philo) * data.n_philo);
	if (!philo)
		return (error_msj(3), EXIT_FAILURE);
	while (++i < data.n_philo)
	{
		philo[i].id = i;
		philo[i].iter = 0;
		philo[i].meal_init = 0;
		philo[i].param = &data;
		philo[i].left_fork = &data.fork[i];
		philo[i].right_fork = 0;
	}
	if (init_thread(&data, philo) == 1)
		return (ft_exit_fail(&data, philo), EXIT_FAILURE);
	check_thread(&data, philo);
	end_thread(&data, philo);
	return (EXIT_SUCCESS);
}
