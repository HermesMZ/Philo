/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:12:55 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/09 18:51:55 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	sem_unlink("/forks_sem");
	free(data);
}

long	get_time_in_ms(void)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000);
}
