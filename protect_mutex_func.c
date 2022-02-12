/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_mutex_func.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:33:29 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/12 11:40:21 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	change_end_value(t_data_philos *data)
{
	pthread_mutex_lock(&data->is_end_control);
	data->is_end = 1;
	pthread_mutex_unlock(&data->is_end_control);
}

int	check_is_end(t_data_philos *data)
{
	pthread_mutex_lock(&data->is_end_control);
	if (data->is_end == 1)
	{
		pthread_mutex_unlock(&data->is_end_control);
		return (1);
	}
	pthread_mutex_unlock(&data->is_end_control);
	return (0);
}

void	change_last_meal_value(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_control);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->last_meal_control);
}

void	add_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->count_eats_control);
	philo->count_eats++;
	pthread_mutex_unlock(&philo->count_eats_control);
}

int	get_count_eats(t_philo *philo)
{
	int	count;

	pthread_mutex_lock(&philo->count_eats_control);
	count = philo->count_eats;
	pthread_mutex_unlock(&philo->count_eats_control);
	return (count);
}
