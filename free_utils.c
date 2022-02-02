/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:55:03 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/02 16:08:40 by achane-l         ###   ########.fr       */
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
        //free(&data->lst_philo[0].forks[i]);
        i++;
    }
    free(data->lst_philo[0].forks);
    i = 0;
    // while (i < data->nb_of_philos)
    // {
    //     free(&data->lst_philo[i]);
    //     i++;
    // }
    free(data->lst_philo);
    pthread_mutex_destroy(data->print_control);
    free(data->print_control);
}