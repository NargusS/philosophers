/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:55:03 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/11 19:10:46 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void    free_data(t_data_philos *data)
{
    int i;
    
    i = 0;
    while (i < data->nb_of_philos)
    {
        pthread_mutex_destroy(&data->lst_philo[0].forks[i]);
        pthread_mutex_destroy(&data->lst_philo[i].last_meal_control);
        pthread_mutex_destroy(&data->lst_philo[i].count_eats_control);
        i++;
    }
    //mutex last meal
    free(data->lst_philo[0].forks);
    free(data->lst_philo);
    pthread_mutex_destroy(&data->print_control);
    pthread_mutex_destroy(&data->is_end_control);
}