/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:02 by achane-l          #+#    #+#             */
/*   Updated: 2022/01/22 02:07:06 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void *routine(void *arg)
{
	lst_philo *data;
	// struct timeval end;
	
	data = (lst_philo *)arg;
	pthread_mutex_lock(&data->mutex_philo);
	// gettimeofday(&end, NULL);
	// printf("%ld\n", data->start.tv_usec);
	printf("Hello, i'm philo %d\n", data->philos[data->current_philo].id);
	data->current_philo++;
	pthread_mutex_unlock(&data->mutex_philo);
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
	while (i++ < philos_lst.nb_of_philos)
		pthread_join(philos_lst.philos[i].philo, NULL);
	return (0);
}