/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 17:14:58 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 14:10:58 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_stop(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (!philo->should_stop)
	{
		if (get_time_in_ms() - philo->last_meal_time > philo->data->time_to_die)
		{
			usleep(1000);
			if (philo->should_stop)
				break ;
			i = 0;
			while (i < philo->data->num_philos)
			{
				sem_post(philo->data->stop);
				i++;
			}
			safe_print(philo, "died");
			cleanup(philo->data);
			exit(0);
		}
		usleep(100);
	}
	return (NULL);
}

void	*monitor_external_stop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	sem_wait(philo->data->stop);
	philo->should_stop = 1;
	return (NULL);
}

void	*monitor_meals(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	if (data->num_meals == -1)
		return (NULL);
	i = 0;
	while (i < data->num_philos)
	{
		sem_wait(data->meals_done);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		sem_post(data->stop);
		i++;
	}
	return (NULL);
}

void	start_philo(t_philo *philo)
{
	pthread_t	stop_thread;
	pthread_t	external_stop_thread;

	philo->last_meal_time = get_time_in_ms();
	if (pthread_create(&stop_thread, NULL, monitor_stop, philo) != 0)
	{
		printf("Error: pthread_create failed");
		exit(1);
	}
	if (pthread_create(&external_stop_thread, NULL, monitor_external_stop,
			philo) != 0)
	{
		printf("Error: pthread_create failed");
		exit(1);
	}
	pthread_detach(stop_thread);
	pthread_detach(external_stop_thread);
	philo_routine(philo);
	cleanup(philo->data);
	exit(0);
}

void	start_simulation(t_data *data)
{
	pthread_t	meals_thread;
	int			i;

	if (pthread_create(&meals_thread, NULL, monitor_meals, data) != 0)
	{
		printf("Error: pthread_create failed");
		return ;
	}
	pthread_detach(meals_thread);
	i = 0;
	while (i < data->num_philos)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			printf("Error: Fork failed.\n");
			cleanup(data);
			return ;
		}
		if (data->pid[i] == 0)
		{
			start_philo(&data->philos[i]);
		}
		i++;
	}
}
