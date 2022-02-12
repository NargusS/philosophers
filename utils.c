/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:17:37 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/12 11:36:29 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	atoi_modify(char *arg)
{
	long long int	num;

	num = 0;
	if (*arg == 0 || *arg == '-' || *arg == '0')
		return (-1);
	while (*arg >= '0' && *arg <= '9')
	{
		num = (num * 10) + (*arg - 48);
		if (num < INT_MIN || num > INT_MAX)
			return (-1);
		arg++;
	}
	if (*arg != '\0')
		return (-1);
	return ((int)num);
}

long int	get_time(void)
{
	struct timeval	time;
	long int		act_time;

	gettimeofday(&time, NULL);
	act_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (act_time);
}

int	custom_usleep(long int ms, t_data_philos *data)
{
	long int	start_time;

	start_time = get_time();
	if (ms <= 0 || check_is_end(data) == 1)
		return (-1);
	while (get_time() - start_time < ms)
	{
		if (check_is_end(data) == 1)
			return (1);
		usleep(100);
	}
	return (1);
}

int	print_status(int message, t_philo *ph)
{
	long int	current;

	current = get_time();
	pthread_mutex_lock(&ph->data->print_control);
	if (check_is_end(ph->data) == 1)
	{
		pthread_mutex_unlock(&ph->data->print_control);
		if (message == TAKEN_FORK || message == EAT)
			unlock_fork(ph, ph->forks);
		return (-1);
	}
	if (message == TAKEN_FORK)
	{
		printf("%ld %d has taken a fork\n", current - ph->time_start, ph->id);
		printf("%ld %d has taken a fork\n", current - ph->time_start, ph->id);
	}
	else if (message == EAT)
		printf("%ld %d is eating\n", current - ph->time_start, ph->id);
	else if (message == SLEEP)
		printf("%ld %d is sleeping\n", current - ph->time_start, ph->id);
	else if (message == THINK)
		printf("%ld %d is thinking\n", current - ph->time_start, ph->id);
	pthread_mutex_unlock(&ph->data->print_control);
	return (1);
}

void	print_death(t_philo *philo, long int time_death)
{
	pthread_mutex_lock(&philo->data->print_control);
	printf("%ld %d is dead\n", time_death - philo->data->time_start, philo->id);
	pthread_mutex_unlock(&philo->data->print_control);
}
