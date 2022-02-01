/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:17:37 by achane-l          #+#    #+#             */
/*   Updated: 2022/02/01 17:21:42 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int atoi_modify(char *arg)
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
	struct timeval time;
	long int act_time;

	gettimeofday(&time, NULL);
	act_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (act_time);
}

// int	diff_time(struct timeval start, struct timeval end)
// {
// 	//fonction pour calculer la diff de temps entre le debut du progamme et le lancement des commandes
// }