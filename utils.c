/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achane-l <achane-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:17:37 by achane-l          #+#    #+#             */
/*   Updated: 2022/01/22 02:07:30 by achane-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int atoi_modify(char *arg)
{
	long long int	num;

	num = 0;
	if (*arg == 0)
		return (-1);
	if (*arg == '-')
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

// int	diff_time(struct timeval start, struct timeval end)
// {
// 	//fonction pour calculer la diff de temps entre le debut du progamme et le lancement des commandes
// }