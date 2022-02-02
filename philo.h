/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:30 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/02 19:41:34 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

typedef	struct s_philo
{
	pthread_t				philo_thread;
	pthread_mutex_t			*forks;
	long int				last_meal;
	int						id;
	int						count_eats;
	struct s_data_philos	*data;
}				t_philo;

typedef struct s_data_philos
{
	pthread_t		control_thread;
	pthread_mutex_t	*print_control;
	long int		time_start;
	int				is_end;
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_eating;
	t_philo			*lst_philo;
}				t_data_philos;

//					UTILS.C						//
int atoi_modify(char *arg);
long int	get_time(void);
//					INIT.C						//
int	init_dining(t_data_philos *data, int argc, char **argv);
void	init_my_philo(t_philo *the_philo, int my_philo, t_data_philos *data, pthread_mutex_t *forks);

void    free_data(t_data_philos *data);
#endif