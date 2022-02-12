/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 12:31:40 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/12 11:35:48 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	lock_fork(t_philo *philo, pthread_mutex_t *forks)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&forks[philo->id % philo->nb_of_philos]);
		pthread_mutex_lock(&forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_lock(&forks[philo->id - 1]);
		pthread_mutex_lock(&forks[philo->id % philo->nb_of_philos]);
	}
}

void	unlock_fork(t_philo *philo, pthread_mutex_t *forks)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&forks[philo->id % philo->nb_of_philos]);
		pthread_mutex_unlock(&forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&forks[philo->id - 1]);
		pthread_mutex_unlock(&forks[philo->id % philo->nb_of_philos]);
	}
}

int	eat_philo(t_philo *philo)
{
	lock_fork(philo, philo->forks);
	if (print_status(TAKEN_FORK, philo) == -1)
		return (-1);
	change_last_meal_value(philo);
	if (print_status(EAT, philo) == -1)
		return (-1);
	if (custom_usleep(philo->time_to_eat, philo->data) == -1)
	{
		unlock_fork(philo, philo->forks);
		return (-1);
	}
	add_eat(philo);
	unlock_fork(philo, philo->forks);
	return (1);
}

int	sleep_and_think_philo(t_philo *philo)
{
	if (print_status(SLEEP, philo) == -1)
		return (-1);
	if (custom_usleep(philo->time_to_sleep, philo->data) == -1)
		return (-1);
	if (print_status(THINK, philo) == -1)
		return (-1);
	if (custom_usleep((philo->time_to_die - (philo->time_to_eat + \
	philo->time_to_sleep)) / 2, philo->data) == -1)
		return (-1);
	return (1);
}

void	*routine_philo(void *arg)
{
	t_philo	*the_philo;

	the_philo = (t_philo *)arg;
	while (check_is_end(the_philo->data) == 0)
	{
		if (eat_philo(the_philo) == -1)
			return (NULL);
		if (sleep_and_think_philo(the_philo) == -1)
			return (NULL);
	}
	return (NULL);
}
