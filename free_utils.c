/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:55:03 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/12 11:32:57 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	destroy_forks(pthread_mutex_t *forks, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&forks[i]);
		i--;
	}
	free(forks);
}

void	destroy_mutex_of_philos(t_philo *philo, int i)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&(philo[i].last_meal_control));
		pthread_mutex_destroy(&(philo[i].count_eats_control));
		i--;
	}
	free(philo);
}

void	destroy_mutex_of_data(t_data_philos *data)
{
	pthread_mutex_destroy(&(data->print_control));
	pthread_mutex_destroy(&(data->is_end_control));
}

void	free_data(t_data_philos *data)
{
	destroy_forks(data->lst_philo[0].forks, data->nb_of_philos - 1);
	destroy_mutex_of_philos(data->lst_philo, data->nb_of_philos - 1);
	destroy_mutex_of_data(data);
}
