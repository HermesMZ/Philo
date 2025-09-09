/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:35:58 by zoum              #+#    #+#             */
/*   Updated: 2025/09/09 16:22:01 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!philo->data->dead)
		printf("%ld %d %s\n", get_time_in_ms(), philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

long	get_time_in_ms(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void	clean_all(t_data *data)
{
	int	i;

	i = 0;
	if (data)
	{
		if (data->philos)
		{
			while (i < data->num_philos)
				pthread_join(data->philos[i++].thread, NULL);
			free(data->philos);
		}
		i = 0;
		if (data->forks)
		{
			while (i < data->num_philos)
				pthread_mutex_destroy(&data->forks[i++]);
			free(data->forks);
		}
		pthread_mutex_destroy(&data->print_mutex);
		pthread_mutex_destroy(&data->data_mutex);
		pthread_mutex_destroy(&data->eating_mutex);
		free(data);
	}
}

void	*start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philos[i].thread, NULL, routine,
			&data->philos[i]);
		i++;
	}
	return (NULL);
}
