/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoum <zoum@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:35:58 by zoum              #+#    #+#             */
/*   Updated: 2025/09/18 14:05:51 by zoum             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_print(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->dead || (philo->data->all_ate >= philo->data->num_philos))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%13ld %3d %s\n", get_time_in_ms() - philo->data->start_time,
		philo->id, message);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

long	get_time_in_ms(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

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
}

void	clean_all(t_data *data)
{
	int	i;

	i = -1;
	if (data)
	{
		if (data->philos)
		{
			while (++i < data->num_philos)
			{
				pthread_join(data->philos[i].thread, NULL);
				pthread_join(data->philos[i].monitor_thread, NULL);
			}
			free(data->philos);
		}
		destroy_mutexes(data);
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
		pthread_create(&data->philos[i].monitor_thread, NULL, monitor_stop,
			&data->philos[i]);
		i++;
	}
	return (NULL);
}
