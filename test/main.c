/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:57:24 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/10 16:41:41 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int time_now(void) //devuelve en milisegundos
{
	struct timeval	now;
    if(gettimeofday(&now, NULL) == 0)//devuelve en microsegundos
        return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
    else
        return(EXIT_FAILURE);
}

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
        write(1, "Error: failed to init mutex.\n",29);
    if(num == 6)
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
//1 ms = 1000 microssegundos
//usleep usa microsegundos.
// numeros_filosofos = numero_de_tenedores, tiempo_morir,
// tiempo_comer, tiempo_dormir, numero_de_veces_que_come

void ft_print_status(t_philo *p, char *str)
{
    printf("%li ", (time_now() - p->param->time));
    printf("%i %s\n",p->id, str);
    
}

void ft_eat(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    ft_print_status(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    ft_print_status(philo, "has taken a fork");
    ft_print_status(philo,"is eating");
    usleep((philo->param->t_eat * 1000));
    philo->last_meal = 0;
    pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
    
}

void sleep_think(t_philo *philo)
{
    //usleep(philo->param->t_sleep);
    
    ft_print_status(philo, "is sleeping");
    usleep((philo->param->t_sleep * 1000));
    ft_print_status(philo, "is thinking");
    
}

void    *thread_function(void *work)
{
    t_philo *philo;
    philo = (t_philo*)work;
    //printf("--------------: id philo %i ---------\n", philo->id);
    
   while (1)
   {
    
    ft_eat(philo);
    sleep_think(philo);
    }
    
    return NULL;
}

int	init_thread(t_param *data, t_philo *philo)
{
    int i;
    
    i = 0;
    while (i < data->n_philo)
    {
        philo[i].right_fork = philo[(i + 1) % data->n_philo].left_fork;
        if (pthread_create(&philo->thread_id, NULL, &thread_function, &philo[i]) != 0)
            return(error_msj(6),EXIT_FAILURE);
        //usleep(1000000);
        i++;  
    }
    
    return 0;
}
// https://github.com/m3zh/philo/blob/master/philo/src/thread_routine.c
// https://github.com/anolivei/Philosophers42



int main(int argc, char **argv)
{
    t_param data;
    t_philo *philo;
    int i;
    i = 0;
    /* pthread_t hilo;
    int valor = 42; */
    data.time = time_now();
    printf("--%li--\n", data.time);
    
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
        philo[i].iter = 0;
        philo[i].param = &data;
        philo[i].last_meal = 0;
        philo[i].left_fork = &data.fork[i];        
        i++;
    }
    
    if (init_thread(&data, philo))
		return (EXIT_FAILURE);

    
    
    /* while (i < data.n_philo)
    {
        printf("id: %i \n", philo[i].id);
        i++;
    } */
    
    
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
    i = 0;
    while (i < data.n_philo)
    {
        pthread_join(philo[i].thread_id,NULL);
        i++;
    }
    
    free(philo);
    return (EXIT_SUCCESS);
}