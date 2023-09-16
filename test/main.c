/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:57:24 by esamad-j          #+#    #+#             */
/*   Updated: 2023/09/01 12:51:37 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_param(int ac, char **av, t_param *data)
{   
    data->n_philo = ft_atoi(av[1]);
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    if(ac == 6)
        data->n_time_eat = ft_atoi(av[5]);
    if(data->n_philo <= 0 || data->t_die <= 0 || data->t_eat <= 0 || data->t_sleep <= 0 || data)
        
}

int main(int argc, char **argv)
{
    t_param data;
    
    if(argc != 5 && argc != 6)
            return(0);
    check_param(argc, argv, &data);
    return 0;
}