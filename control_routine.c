/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:33:45 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/11 19:09:04 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int		philos_are_alive(t_data_philos *data)
{
	//long int	last_meal;
	long int	current;
	t_philo		*philos;
	int i;

	i = 0;
	philos = data->lst_philo;
	while (i < data->nb_of_philos)
	{
		// last_meal = get_last_meal(&philos[i]);
		current = get_time();
		pthread_mutex_lock(&philos[i].last_meal_control);
		if (current - philos[i].last_meal >= data->time_to_die)
		{
			change_end_value(data);
			pthread_mutex_lock(&data->print_control);
			printf("timestamp %ld ms,philo %d is dead\n", current - data->time_start,philos[i].id);
			pthread_mutex_unlock(&philos[i].last_meal_control);
			pthread_mutex_unlock(&data->print_control);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].last_meal_control);
		if (check_is_end(data) == 1)
		{
			pthread_mutex_lock(&data->print_control);
			printf("timestamp %ld ,philo %d is dead\n", get_time() - data->time_start, philos[i].id);
			pthread_mutex_unlock(&data->print_control);
			return (0);
		}
		i++;
	}
	return (1);
}

int		philos_all_eat(t_data_philos *data)
{
	int i;
	t_philo *philos;

	i = 0;
	if (data->nb_of_eating == -1)
		return (0);
	philos = data->lst_philo;
	while (i < data->nb_of_philos)
	{
		if (get_count_eats(&philos[i]) < data->nb_of_eating)
			return (0);
		i++;
	}
	return (1);
}

void	*routine_control(void *arg)
{
	t_data_philos *data;

	data = (t_data_philos *)arg;
	while (philos_are_alive(data) == 1)
	{
		if (philos_all_eat(data) == 1)
		{
			change_end_value(data);
			pthread_mutex_lock(&data->print_control);
			printf("ALL eat \n");
			pthread_mutex_unlock(&data->print_control);
			return (NULL);
		}
		usleep(100);
	}
	return (NULL);
}
