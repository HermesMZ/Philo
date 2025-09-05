/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:35:58 by zoum              #+#    #+#             */
/*   Updated: 2025/09/05 01:48:30 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		free(data);
	}
	pthread_mutex_destroy(&data->print_mutex);
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
