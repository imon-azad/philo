/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:04:53 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/10 02:46:43 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_param
{
    int n_philo;
    int t_die;
    int t_eat;
    int t_sleep;
    int n_time_eat;
    pthread_mutex_t *fork;

    
    
    
}   t_param;

typedef struct s_philo
{
    int id;
    int dead;
    int meal;
    int iter;
    t_param *param;
    pthread_t		thread_id; //id del hilo creado
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    
}   t_philo;


int	ft_atoi(const char *str);
