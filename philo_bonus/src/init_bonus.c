/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:13:16 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/09 18:49:34 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data	*init_philos_and_semaphore(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
		return (free(data), NULL);
	data->forks = sem_open("/forks_sem", O_CREAT, 0644, data->num_philos);
	if (data->forks == SEM_FAILED)
		return (free(data->philos), free(data), NULL);
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = get_time_in_ms();
		data->philos[i].data = data;
		i++;
	}
	return (data);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	data->start_time = get_time_in_ms();
	data = init_philos_and_semaphore(data);
	if (!data)
		return (NULL);
	return (data);
}
