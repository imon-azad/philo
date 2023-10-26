/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:04:53 by esamad-j          #+#    #+#             */
/*   Updated: 2023/10/26 17:37:47 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_param
{
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_time_eat;
	int				ready;
	int				finish_flag;
	int				meal_flag;
	long int		time;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*death;
	pthread_mutex_t	*printer;
}					t_param;

typedef struct s_philo
{
	int				id;
	int				iter;
	long int		meal_init;
	t_param			*param;
	pthread_t		thread_id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philo;

/*param check and inits*/
int					check_param(int ac, char **av, t_param *data);
int					init_mutex(t_param *data);

/*Thread*/
int					init_thread(t_param *data, t_philo *philo);
void				*thread_function(void *work);
int					check_thread(t_param *data, t_philo *philo);
void				end_thread(t_param *data, t_philo *philo);
int					check_death(t_philo *philo);
int					check_meals(t_philo philo, int last);

/*Exit*/
void				error_msj(int num);
void				ft_exit_fail(t_param *data, t_philo *philo);

/*Libft*/
int					ft_atoi(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/*Utils*/
long int			time_now(void);
void				ft_print_status(t_philo *p, char *str);
void				ft_usleep(long int time);

#endif