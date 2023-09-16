/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:04:53 by esamad-j          #+#    #+#             */
/*   Updated: 2023/08/31 14:12:02 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_param
{
    int n_philo;
    int t_die;
    int t_eat;
    int t_sleep;
    int n_time_eat;
    int n_forks;
    
}   t_param;


int	ft_atoi(const char *str);
