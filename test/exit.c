/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:34:52 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/26 17:02:36 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_msj(int num)
{
	if (num == 1)
		write(1, "Error: invalid number of arguments.\n", 36);
	if (num == 2)
		write(1, "Error: invalid arguments.\n", 26);
	if (num == 3)
		write(1, "Error: malloc failed.\n", 22);
	if (num == 4)
		write(1, "Error: mutex init failed.\n", 26);
	if (num == 5)
		write(1, "Error: failed to init mutex.\n", 29);
	if (num == 6)
		write(1, "Error: failed to create thread.\n", 32);
}

void	ft_exit_fail(t_param *data, t_philo *philo)
{
	pthread_mutex_destroy(data->death);
	pthread_mutex_destroy(data->fork);
	pthread_mutex_destroy(data->printer);
	free(data->death);
	free(data->fork);
	free(data->printer);
	free(philo);
}

void	end_thread(t_param *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(philo[i].thread_id, NULL);
		i++;
	}
	pthread_mutex_destroy(data->death);
	pthread_mutex_destroy(data->fork);
	pthread_mutex_destroy(data->printer);
	free(data->death);
	free(data->fork);
	free(data->printer);
	free(philo);
}
