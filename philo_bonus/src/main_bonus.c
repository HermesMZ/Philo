/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:10:10 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/17 14:04:16 by mzimeris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_input(int argc, char *argv[])
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (0);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] > '9' || argv[i][j] < '0' || j > 10)
				return (printf("Error: Invalid input\n"), 0);
			j++;
		}
		if (ft_atoi(argv[i]) != ft_atol(argv[i])
			|| ft_atoi(argv[i]) > 2147483647)
			return (printf("Error: Invalid input\n"), 0);
		i++;
	}
	return (1);
}

void	wait_and_cleanup(t_data *data)
{
	int		i;
	int		status;

	waitpid(-1, &status, 0);
	i = 0;
	while (i < data->num_philos)
	{
		sem_post(data->stop);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		kill(data->pid[i], 9);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
	final_cleanup(data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid number of arguments.\n"), 1);
	if (!check_input(argc, argv))
		return (1);
	data = init_data(argc, argv);
	if (!data)
		return (printf("Error: Failed to initialize data.\n"), 1);
	start_simulation(data);
	wait_and_cleanup(data);
	return (0);
}
