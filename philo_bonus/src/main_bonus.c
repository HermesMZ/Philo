/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzimeris <mzimeris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:10:10 by mzimeris          #+#    #+#             */
/*   Updated: 2025/09/09 18:28:07 by mzimeris         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	t_data	*data;
	int		i;

	if (argc != 5 && argc != 6)
		return (printf("Error: Invalid number of arguments.\n"), 1);
	if (!check_input(argc, argv))
		return (1);
	data = init_data(argc, argv);
	if (!data)
		return (printf("Error: Failed to initialize data.\n"), 1);
	i = 0;
	while (i < data->num_philos)
	{
		if (fork() == 0)
		{
			philo_routine(&data->philos[i]);
			exit(0);
		}
		i++;
	}
	cleanup(data);
	return (0);
}
