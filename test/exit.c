/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:34:52 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/26 14:19:23 by esamad-j         ###   ########.fr       */
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
        write(1, "Error: failed to init mutex.\n",29);
    if(num == 6)
        write(1, "Error: failed to create thread.\n",32);
}


