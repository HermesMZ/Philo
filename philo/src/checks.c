/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:20:15 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/18 14:06:40 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_stop(t_philo *philo)
{
	int	result;

	pthread_mutex_lock(&philo->data->data_mutex);
	result = (philo->data->dead || philo->data->all_ate
			== philo->data->num_philos);
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (result);
}

int	check_death(t_philo *philo)
{
	long	last_meal;

	pthread_mutex_lock(&philo->data->eating_mutex);
	last_meal = philo->last_meal_time;
	pthread_mutex_unlock(&philo->data->eating_mutex);
	if (get_time_in_ms() - last_meal > philo->data->time_to_die)
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

void	*monitor_stop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->dead || philo->data->all_ate
			== philo->data->num_philos)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
		if (check_death(philo))
			break ;
		usleep(1000);
	}
	return (NULL);
}
