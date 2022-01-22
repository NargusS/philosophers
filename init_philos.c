/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:11:49 by achane-l          #+#    #+#             */
/*   Updated: 2022/01/21 19:01:46 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_lst_philo(lst_philo *philo_lst, int argc, char **argv)
{
	int	i;

	philo_lst->nb_of_philos = atoi_modify(argv[1]);
	philo_lst->time_to_die = atoi_modify(argv[2]);
	philo_lst->time_to_eat = atoi_modify(argv[3]);
	philo_lst->time_to_sleep = atoi_modify(argv[4]);
	if (argc == 6)
		philo_lst->nb_of_eating = atoi_modify(argv[5]);
	if (philo_lst->nb_of_philos == -1 || philo_lst->time_to_die == -1 || \
	philo_lst->time_to_eat == -1 || philo_lst->time_to_sleep == -1 || \
	philo_lst->nb_of_eating == -1)
		return (-1);
	philo_lst->philos = malloc(sizeof(my_philo) * philo_lst->nb_of_philos);
	if (philo_lst == NULL)
		return (-1);
	i = 0;
	while (i < philo_lst->nb_of_philos)
	{
		init_my_philo(&philo_lst->philos[i], i);
		i++;
	}
	gettimeofday(&philo_lst->start, NULL);
	pthread_mutex_init(&philo_lst->mutex_philo,NULL);
	return (1);
}

void	init_my_philo(my_philo *the_philo, int my_philo)
{
	the_philo->id = my_philo;
	the_philo->forks = 1;
	the_philo->count_eats = 0;
	the_philo->sleep_time = 0;
	the_philo->eat_time = 0;
	the_philo->die_time = 0;
}