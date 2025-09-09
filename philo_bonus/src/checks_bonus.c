/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:46:07 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/09 18:49:20 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	death_check(t_philo *philo)
{
	if (get_time_in_ms() - philo->last_meal_time > philo->data->time_to_die)
	{
		printf("%ld %d died\n", get_time_in_ms(), philo->id);
		return (1);
	}
	return (0);
}

int	stop_check(t_philo *philo)
{
	int	result;

	(void)philo;
	result = 0;
	return (result);
}
