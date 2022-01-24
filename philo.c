/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:02 by achane-l          #+#    #+#             */
/*   Updated: 2022/01/22 19:06:48 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_philo(lst_philo *data)
{
	printf("%ld ms %d is eating %d forks\n", get_time() - data->time_start, data->philos[data->current_philo].id, data->philos[data->current_philo].forks);
	usleep(data->time_to_eat/100);
	data->philos[data->current_philo].count_eats++;
	data->philos[data->current_philo].has_eat++;
}

void	sleep_philo(lst_philo *data)
{
	printf("%ld ms %d is sleeping\n", get_time() - data->time_start, data->philos[data->current_philo].id);
	usleep(data->time_to_sleep/100);
	data->philos[data->current_philo].has_sleep++;
}

void	think_philo(lst_philo *data)
{
	printf("%ld ms %d is thinking\n", get_time() - data->time_start, data->philos[data->current_philo].id);
	data->philos[data->current_philo].has_think++;
}

void	keep_fork(lst_philo *data)
{
	if (data->current_philo == 0)
	{
		data->philos[data->nb_of_philos-1].forks -= 1;
		data->philos[0].forks += 1;
	}
	else
	{
		data->philos[data->current_philo - 1].forks -= 1;
		data->philos[data->current_philo].forks += 1;
	}
}

void	give_fork(lst_philo *data)
{
	if (data->current_philo == 0)
	{
		data->philos[0].forks -= 1;
		data->philos[data->nb_of_philos-1].forks += 1;
	}
	else
	{
		data->philos[data->current_philo].forks -= 1;
		data->philos[data->current_philo - 1].forks += 1;
	}
}

void *routine(void *arg)
{
	lst_philo *data;
	
	data = (lst_philo *)arg;
	int i = 0;
	while (i < 5)
	{
		pthread_mutex_lock(&data->mutex_philo);
		// if (data->philos[data->current_philo].forks == 1 && data->philos[data->current_philo].has_eat == 0)
		// {
		// 	if (data->current_philo == 0)
		// 	{
		// 		keep_fork(data);
		// 		eat_philo(data);
		// 		give_fork(data);
		// 	}
		// 	else
		// 	{
		// 		if (data->philos[data->current_philo-1].has_eat == 1)
		// 		{
		// 			keep_fork(data);
		// 			eat_philo(data);
		// 			give_fork(data);
		// 		}
		// 	}
		// }
		if (data->philos[data->current_philo].has_eat == 0 && data->philos[data->current_philo].forks == 1)
			eat_philo(data);
		else if (data->philos[data->current_philo].has_eat == 1 && data->philos[data->current_philo].has_sleep == 0)
			sleep_philo(data);
		else if (data->philos[data->current_philo].has_eat == 1 && data->philos[data->current_philo].has_sleep == 1)
		{
			data->philos[data->current_philo].has_eat = 0;
			data->philos[data->current_philo].has_sleep = 0;
			think_philo(data);
		}
		// else
		if (data->current_philo < data->nb_of_philos - 1)
			data->current_philo++;
		else
			data->current_philo = 0;
		pthread_mutex_unlock(&data->mutex_philo);
		i++;
	}
	// gettimeofday(&end, NULL);
		// printf("%ld ms %d do something...\n", get_time() - data->time_start,data->philos[data->current_philo].id);
	// printf("%ld\n", data->start.tv_usec);
	return (NULL);
}


int main(int argc, char **argv)
{
	lst_philo philos_lst;
	int i;

	if (argc < 5 || argc > 6 || init_lst_philo(&philos_lst, argc, argv) == -1)
		return (-1);
	i = 0;
	philos_lst.current_philo = 0;
	while (i < philos_lst.nb_of_philos)
	{
		pthread_create(&philos_lst.philos[i].philo,NULL, &routine, (void *)&philos_lst);
		i++;
	}
	i = 0;
	while (i < philos_lst.nb_of_philos)
	{
		pthread_join(philos_lst.philos[i].philo, NULL);
		i++;
	}
	return (0);
}
