/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:11:49 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/01 17:35:52 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_dining(t_data_philos *data, int argc, char **argv)
{
	int	i;

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
	data->nb_of_eating == -1 && argc == 6)
		return (-1);
	data->lst_philo = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (data == NULL)
		return (-1);
	data->time_start = get_time();
	i = 0;
	while (i < data->nb_of_philos)
	{
		init_my_philo(&data->lst_philo[i], i, data);
		i++;
	}
	data->print_control = malloc(sizeof(pthread_mutex_t));
	if (data->print_control == NULL)
		return (-1);
	pthread_mutex_init(data->print_control, NULL);
	return (1);
}

void	init_my_philo(t_philo *the_philo, int my_philo, t_data_philos *data)
{
	the_philo->last_meal = get_time();
	the_philo->id = my_philo;
	the_philo->forks = 1;
	the_philo->count_eats = 0;
	the_philo->data = data;
}