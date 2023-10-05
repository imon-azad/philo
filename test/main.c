/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:57:24 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/05 04:15:21 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void error_msj(int num)
{
    if(num == 1)
        write(1, "Error: invalid number of arguments.\n",36);
    if(num == 2)
        write(1, "Error: invalid arguments.\n",26);
    if(num == 3)
        write(1, "Error: malloc failed.\n",22);
    if(num == 4)
        write(1, "Error: mutex init failed.\n",26);
    if(num == 5)
        write(1, "Error: failed to create thread.\n",32);
    
}

int init_mutex(t_param *data)
{
    int i;

    i = 0;
    data->fork = 0;
    data->fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
    if(!data->fork)
        return(error_msj(3), -1);
    while(i < data->n_philo)
    {  
        if(pthread_mutex_init(&data->fork[i], NULL) == -1)
            return(error_msj(5), -1);
        i++;
    }
    return(0);
}


int check_param(int ac, char **av, t_param *data)
{   
    data->n_philo = ft_atoi(av[1]);
    data->t_die = ft_atoi(av[2]);
    data->t_eat = ft_atoi(av[3]);
    data->t_sleep = ft_atoi(av[4]);
    
    if(ac == 6)
    {
        data->n_time_eat = ft_atoi(av[5]);
        if(data->n_time_eat <= 0)
            return (error_msj(2), EXIT_FAILURE);
    }
    if(data->n_philo)
        if(init_mutex(data) == -1)
            return(EXIT_FAILURE);
            
    if(data->n_philo <= 0 || data->t_die <= 0 || data->t_eat <= 0 || data->t_sleep <= 0)
        return (error_msj(2), EXIT_FAILURE); 
    return (EXIT_SUCCESS);
}
// 1 Segundo = 1000 milisegundos
// numeros_filosofos = numero_de_tenedores, tiempo_morir,
// tiempo_comer, tiempo_dormir, numero_de_veces_que_come

void *mi_funcion(void *arg) {
    int *numero = (int *)arg;
    printf("Hola desde el hilo. Valor recibido: %d\n", *numero);
    return NULL;
}

void    thread_function(void *work)
{

    
}

int	init_thread(t_param *data, t_philo *philo)
{
    int i;
    
    i = 0;
    while (i < data->n_philo)
    {
        philo[i].right_fork = philo[(i + 1) % data->n_philo].left_fork;
        if (pthread_create(&philo->thread_id, NULL, mi_funcion, &philo[i]) != 0)
            return(error_msj(5),EXIT_FAILURE);
    }
    
    
}

int main(int argc, char **argv)
{
    t_param data;
    t_philo *philo;
    int i;
    i = 0;
    /* pthread_t hilo;
    int valor = 42; */
    
    if(argc != 5 && argc != 6)
            return(error_msj(1),EXIT_FAILURE);
    if(check_param(argc, argv, &data) == EXIT_FAILURE)
        return(EXIT_FAILURE);       
    philo = malloc(sizeof(t_philo) * data.n_philo);
    while(i < data.n_philo)
    {
        philo[i].id = i;
        philo[i].dead = 0;
        philo[i].meal = 0;
        philo[i].left_fork = data.fork[i];        
        i++;
    }
    
    if (init_thread(&data, philo))
		return (EXIT_FAILURE);

    
    i = 0;
    while (i < data.n_philo)
    {
        printf("id: %i \n", philo[i].id);
        i++;
    }
    
    
  /*   if (pthread_create(&hilo, NULL, mi_funcion, &valor) != 0) {
        perror("Error al crear el hilo");
        return 1;
    }
  if (pthread_join(hilo, NULL) != 0) {
        perror("Error al unirse al hilo");
        return 1;
    }

    printf("Hilo terminado\n");
     */
    free(philo);
    return (EXIT_SUCCESS);
}