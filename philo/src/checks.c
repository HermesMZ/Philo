/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:20:15 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/09 17:20:42 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_philo *philo)
{
	if (get_time_in_ms() - philo->last_meal_time > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (!philo->data->dead)
		{
			safe_print(philo, "died");
			philo->data->dead = 1;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (1);
	}
	return (0);
}

int	stop_check(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->data_mutex);
	result = (philo->data->dead || philo->data->all_ate
			== philo->data->num_philos);
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (result);
}
