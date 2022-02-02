/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:47:02 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/02 20:59:42 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	custom_usleep(long int ms, t_data_philos *data)
{
	long int start_time;

	if (ms <= 0)
		return ;
	start_time = get_time();
	while(get_time() - start_time < ms)
	{
		if (data->is_end == 1)
			break;
	}
	return;
}

void	lock_fork(t_philo *philo, pthread_mutex_t *forks)
{
	// if (philo->id % 2 == 0)
	// {
	// 	pthread_mutex_lock(&forks[philo->id - 1]);
	// 	pthread_mutex_lock(&forks[philo->id % philo->data->nb_of_philos]);
	// }
	// else
	// {
	// 	pthread_mutex_lock(&forks[philo->id % philo->data->nb_of_philos]);
	// 	pthread_mutex_lock(&forks[philo->id - 1]);
	// }
	if (philo->id - 1 > philo->id % philo->data->nb_of_philos)
	{
		pthread_mutex_lock(&forks[philo->id % philo->data->nb_of_philos]);
		pthread_mutex_lock(&forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_lock(&forks[philo->id - 1]);
		pthread_mutex_lock(&forks[philo->id % philo->data->nb_of_philos]);
	}
}

void	unlock_fork(t_philo *philo, pthread_mutex_t *forks)
{
	// if (philo->id % 2 == 0)
	// {
	// 	pthread_mutex_unlock(&forks[philo->id - 1]);
	// 	pthread_mutex_unlock(&forks[philo->id % philo->data->nb_of_philos]);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(&forks[philo->id % philo->data->nb_of_philos]);
	// 	pthread_mutex_unlock(&forks[philo->id - 1]);
	// }
	if (philo->id - 1 > philo->id % philo->data->nb_of_philos)
	{
		pthread_mutex_unlock(&forks[philo->id % philo->data->nb_of_philos]);
		pthread_mutex_unlock(&forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&forks[philo->id - 1]);
		pthread_mutex_unlock(&forks[philo->id % philo->data->nb_of_philos]);
	}
}

void	eat_philo(t_philo *philo)
{
	lock_fork(philo, philo->forks);
	pthread_mutex_lock(philo->data->print_control);
	if (philo->data->is_end == 1)
	{
		pthread_mutex_unlock(philo->data->print_control);
		unlock_fork(philo, philo->forks);
		return ;
	}
	philo->last_meal = get_time();
	printf("%ld ms %d take left fork...\n", get_time() - philo->data->time_start, philo->id);
	printf("%ld ms %d take right fork...\n", get_time() - philo->data->time_start, philo->id);
	pthread_mutex_unlock(philo->data->print_control);
	pthread_mutex_lock(philo->data->print_control);
	if (philo->data->is_end == 1)
	{
		pthread_mutex_unlock(philo->data->print_control);
		unlock_fork(philo, philo->forks);
		return ;
	}
	printf("%ld ms %d is eating...\n", get_time() - philo->data->time_start, philo->id);
	pthread_mutex_unlock(philo->data->print_control);
	custom_usleep(philo->data->time_to_eat, philo->data);
	//usleep(philo->data->time_to_eat*1000);
	philo->count_eats++;
	// pthread_mutex_lock(philo->data->print_control);
	// if (philo->data->is_end == 1)
	// {
	// 	pthread_mutex_unlock(philo->data->print_control);
	// 	unlock_fork(philo, philo->forks);
	// 	return ;
	// }
	// printf("%ld ms %d put left fork...\n", get_time() - philo->data->time_start, philo->id);
	// printf("%ld ms %d put right fork...\n", get_time() - philo->data->time_start, philo->id);
	// pthread_mutex_unlock(philo->data->print_control);
	unlock_fork(philo, philo->forks);
	return;
}

void	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print_control);
	if (philo->data->is_end == 1)
	{
		pthread_mutex_unlock(philo->data->print_control);
		return ;
	}
	printf("%ld ms %d is sleeping\n", get_time() - philo->data->time_start, philo->id);
	pthread_mutex_unlock(philo->data->print_control);
	custom_usleep(philo->data->time_to_sleep, philo->data);
	// usleep(philo->data->time_to_sleep*1000);
	return ;
}

void	think_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->data->print_control);
	if (philo->data->is_end == 1)
	{
		pthread_mutex_unlock(philo->data->print_control);
		return ;
	}
	printf("%ld ms %d is thinking\n", get_time() - philo->data->time_start, philo->id);
	pthread_mutex_unlock(philo->data->print_control);
	return ;
}

void	*routine_philo(void *arg)
{
	t_philo *the_philo;

	the_philo = (t_philo *)arg;
	while (the_philo->data->is_end != 1)
	{
		eat_philo(the_philo);
		if (the_philo->data->is_end == 1)
			break;
		sleep_philo(the_philo);
		if (the_philo->data->is_end == 1)
			break;
		think_philo(the_philo);
	}
	return (NULL);
}

int		philos_are_alive(t_data_philos *data)
{
	int i;
	t_philo *philos;
	long int	current_time;

	i = 0;
	philos = data->lst_philo;
	while (i < data->nb_of_philos)
	{
		if (data->is_end == 1)
		{
			data->is_end = 1;
			current_time = get_time();
			pthread_mutex_lock(data->print_control);
			printf("timestamp %ld ,philo %d is dead\n", current_time - data->time_start, philos[i].id);
			pthread_mutex_unlock(data->print_control);
			return (0);
		}
		if (get_time() - philos[i].last_meal >= data->time_to_die)
		{
			data->is_end = 1;
			current_time = get_time();
			pthread_mutex_lock(data->print_control);
			printf("timestamp %ld ms,philo %d is dead\n",  current_time - data->time_start,philos[i].id);
			pthread_mutex_unlock(data->print_control);
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
		if (philos[i].count_eats < data->nb_of_eating)
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
			data->is_end = 1;
			pthread_mutex_lock(data->print_control);
			printf("ALL eat \n");
			pthread_mutex_unlock(data->print_control);
			return (NULL);
		}
		//usleep(100);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_data_philos data;
	int i;

	if (argc < 5 || argc > 6 || init_dining(&data, argc, argv) == -1)
		return (-1);
	i = 0;
	while (i < data.nb_of_philos)
	{
		pthread_create(&data.lst_philo[i].philo_thread,NULL, &routine_philo, (void *)&data.lst_philo[i]);
		i++;
	}
	pthread_create(&data.control_thread,NULL, &routine_control, (void *)&data);
	i = 0;
	while (i < data.nb_of_philos)
	{
		pthread_join(data.lst_philo[i].philo_thread, NULL);
		i++;
	}
	pthread_join(data.control_thread, NULL);
	free_data(&data);
	return (0);
}
