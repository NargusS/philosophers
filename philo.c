/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:02 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/12 11:54:18 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launch_thread(t_data_philos *data, int even_or_odd)
{
	while (even_or_odd < data->nb_of_philos)
	{
		if (pthread_create(&data->lst_philo[even_or_odd].philo_thread, NULL, \
		&routine_philo, (void *)&data->lst_philo[even_or_odd]) != 0)
		{
			printf("Error : pthread_create with philo %d", \
			data->lst_philo[even_or_odd].id);
			return (-1);
		}
		even_or_odd += 2;
	}
	return (1);
}

void	one_philo(t_philo *philo)
{
	printf("%ld %d has taken a fork\n", get_time() - philo->time_start, \
	philo->id);
	usleep(philo->time_to_die * 1000);
	printf("%ld %d is dead\n", get_time() - philo->time_start, philo->id);
}

void	end_thread(t_data_philos *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_join(data->lst_philo[i].philo_thread, NULL);
		i++;
	}
	free_data(data);
}

int	main(int argc, char **argv)
{
	t_data_philos	data;

	if (argc < 5 || argc > 6 || init_dining(&data, argc, argv) == -1)
		return (-1);
	if (data.nb_of_philos > 1)
	{
		if (launch_thread(&data, 1) == -1)
		{
			free_data(&data);
			return (-1);
		}
		if (launch_thread(&data, 0) == -1)
		{
			free_data(&data);
			return (-1);
		}
		routine_control((void *)&data);
		end_thread(&data);
	}
	else
	{
		one_philo(&data.lst_philo[0]);
		free_data(&data);
	}
	return (0);
}
