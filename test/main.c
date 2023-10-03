/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:57:24 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/03 01:24:33 by esamad-j         ###   ########.fr       */
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
    {
        data->n_time_eat = ft_atoi(av[5]);
        if(data->n_time_eat <= 0)
            return (error_msj(2), EXIT_FAILURE);
    }
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
void error_msj(int num)
{
    if(num == 1)
        write(1, "Error: invalid number of arguments.\n",36);
    if(num == 2)
        write(1, "Error: invalid arguments.\n",26);
    
}

int main(int argc, char **argv)
{
    t_param data;
    t_philo *philo;
    
    /* pthread_t hilo;
    int valor = 42; */
    
    if(argc != 5 && argc != 6)
            return(error_msj(1),EXIT_FAILURE);
    if(check_param(argc, argv, &data) == EXIT_FAILURE)
        return(EXIT_FAILURE);       
    philo = malloc(sizeof(t_philo) * data.n_philo);
    
    
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