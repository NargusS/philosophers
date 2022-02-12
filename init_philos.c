/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:11:49 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/12 12:25:52 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_dining(t_data_philos *data, int argc, char **argv)
{
	data->nb_of_philos = atoi_modify(argv[1]);
	data->time_to_die = atoi_modify(argv[2]);
	data->time_to_eat = atoi_modify(argv[3]);
	data->time_to_sleep = atoi_modify(argv[4]);
	if (argc == 6)
		data->nb_of_eating = atoi_modify(argv[5]);
	else
		data->nb_of_eating = -1;
	if (data->nb_of_philos == -1 || data->time_to_die == -1 || \
	data->time_to_eat == -1 || data->time_to_sleep == -1 || \
	(data->nb_of_eating == -1 && argc == 6))
		return (-1);
	data->time_start = get_time();
	data->is_end = 0;
	if (init_mutex(data) == -1)
		return (-1);
	if (init_lst_philos(data) == -1)
	{
		destroy_mutex_of_data(data);
		return (-1);
	}
	return (1);
}

int	init_mutex(t_data_philos *data)
{
	if (pthread_mutex_init(&data->print_control, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&data->is_end_control, NULL) != 0)
	{
		pthread_mutex_destroy(&data->print_control);
		return (-1);
	}
	return (1);
}

pthread_mutex_t	*init_forks(int nb_of_philos)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * nb_of_philos);
	if (forks == NULL)
		return (NULL);
	while (i < nb_of_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			destroy_forks(forks, i - 1);
			return (NULL);
		}
		i++;
	}
	return (forks);
}

int	init_my_philo(t_philo *philo, int id, t_data_philos *data, \
pthread_mutex_t *forks)
{
	if (pthread_mutex_init(&philo->last_meal_control, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&philo->count_eats_control, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->last_meal_control);
		return (-1);
	}
	philo->forks = forks;
	philo->last_meal = get_time();
	philo->id = id + 1;
	philo->count_eats = 0;
	philo->time_start = data->time_start;
	philo->nb_of_philos = data->nb_of_philos;
	philo->time_to_die = data->time_to_die;
	philo->time_to_eat = data->time_to_eat;
	philo->time_to_sleep = data->time_to_sleep;
	philo->nb_of_eating = philo->nb_of_eating;
	philo->data = data;
	return (1);
}

int	init_lst_philos(t_data_philos *data)
{
	pthread_mutex_t	*forks;
	t_philo			*lst_philo;
	int				i;

	i = -1;
	lst_philo = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (lst_philo == NULL)
		return (-1);
	forks = init_forks(data->nb_of_philos);
	if (forks == NULL)
	{
		free(lst_philo);
		return (-1);
	}
	while (++i < data->nb_of_philos)
	{
		if (init_my_philo(&lst_philo[i], i, data, forks) == -1)
		{
			destroy_forks(forks, data->nb_of_philos - 1);
			destroy_mutex_of_philos(lst_philo, i - 1);
			return (-1);
		}
	}
	data->lst_philo = lst_philo;
	return (1);
}
