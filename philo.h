/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:04:53 by esamad-j          #+#    #+#             */
/*   Updated: 2023/11/02 16:02:17 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_world
{
	int				numbers_philo;
	int				time_2_die;
	int				time_2_eat;
	int				time_2_sleep;
	int				max_iter;
	int				max_iter_flag;
	int				ready;
	int				finish_flag;
	long long		time;

	pthread_mutex_t	*fork;
	pthread_mutex_t	death;
	pthread_mutex_t	printer;
	pthread_mutex_t	data_saver;
	pthread_mutex_t	ready_mutex;

}					t_world;

typedef struct s_philo
{
	int				id;
	int				iter;
	long long		meal_init;
	t_world			*world;
	pthread_t		thread_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;

}					t_philo;

int					check_param(int ac, char **av, t_world *world);
void				error_msj(int num);
int					ft_atoi(char *str);
int					check_if_all_numbers(char *num);
long long			time_now(void);
void				end_thread(t_world *world, t_philo *philo);
int					init_mutex(t_world *world);
void				*thread_function(void *work);
void				ft_usleep(long long time);
int					check_thread(t_world *world, t_philo *philo);
int					init_world(int argc, char **argv, t_world **world);
int					init_thread(t_world *world, t_philo *philo);
void				eat_sleep_think(t_philo *philo);
void				ft_print_status(t_philo *p, char *str);
int					check_death(t_philo *philo, t_world *world);
int					check_meals(t_philo philo, int last_philo_id);

#endif