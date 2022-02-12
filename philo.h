/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:30 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/12 12:30:54 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define TAKEN_FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_philo
{
	pthread_t				philo_thread;
	pthread_mutex_t			*forks;
	pthread_mutex_t			last_meal_control;
	pthread_mutex_t			count_eats_control;
	long int				last_meal;
	int						id;
	int						count_eats;
	long int				time_start;
	int						nb_of_philos;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						nb_of_eating;
	struct s_data_philos	*data;
}				t_philo;

typedef struct s_data_philos
{
	pthread_mutex_t	print_control;
	pthread_mutex_t	is_end_control;
	int				is_end;
	long int		time_start;
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_eating;
	t_philo			*lst_philo;
}				t_data_philos;

//					UTILS.C						//
int				atoi_modify(char *arg);
long int		get_time(void);
int				custom_usleep(long int ms, t_data_philos *data);
int				print_status(int message, t_philo *philo);
void			print_death(t_philo *philo, long int time_death);
//					INIT.C						//
int				init_dining(t_data_philos *data, int argc, char **argv);
int				init_mutex(t_data_philos *data);
pthread_mutex_t	*init_forks(int nb_of_philos);
int				init_my_philo(t_philo *philo, int id, t_data_philos *data, \
pthread_mutex_t *forks);
int				init_lst_philos(t_data_philos *data);
//					FREE_UTILS.C						//
void			destroy_forks(pthread_mutex_t *forks, int i);
void			destroy_mutex_of_philos(t_philo *philo, int i);
void			destroy_mutex_of_data(t_data_philos *data);
void			free_data(t_data_philos *data);
//					CONTROL_ROUTINE.C						//
int				philos_are_alive(t_data_philos *data);
int				philos_all_eat(t_data_philos *data);
void			*routine_control(void *arg);
//					PHILO_ROUTINE.C						//
void			lock_fork(t_philo *philo, pthread_mutex_t *forks);
void			unlock_fork(t_philo *philo, pthread_mutex_t *forks);
int				eat_philo(t_philo *philo);
int				sleep_and_think_philo(t_philo *philo);
void			*routine_philo(void *arg);
//					PROTECT_MUTEX_FUNC.C				//
void			change_end_value(t_data_philos *data);
int				check_is_end(t_data_philos *data);
void			change_last_meal_value(t_philo *philo);
void			add_eat(t_philo *philo);
int				get_count_eats(t_philo *philo);
#endif