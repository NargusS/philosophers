/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:30 by achane-l          #+#    #+#             */
/*   Updated: 2022/01/21 18:52:49 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <stdlib.h>

typedef	struct my_philo
{
	pthread_t	philo;
	int			id;
	int			forks;
	int			count_eats;
	int			sleep_time;
	int			eat_time;
	int			die_time;
}				my_philo;

typedef	struct lst_philo
{
	my_philo		*philos;
	struct timeval	start;
	pthread_mutex_t	mutex_philo;
	int				current_philo;
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_eating;
}				lst_philo;


//					UTILS.C						//
int atoi_modify(char *arg);
//					INIT.C						//
int	init_lst_philo(lst_philo *philo_lst, int argc, char **argv);
void	init_my_philo(my_philo *the_philo, int my_philo);
#endif