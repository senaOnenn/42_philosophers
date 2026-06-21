/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 14:39:37 by eonen             #+#    #+#             */
/*   Updated: 2026/06/20 17:03:36 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo count time_die time_eat time_sleep [meals]\n");
		return (1);
	}
	data->num_philos = ft_atoi_philo(argv[1]);
	data->time_to_die = ft_atoi_philo(argv[2]);
	data->time_to_eat = ft_atoi_philo(argv[3]);
	data->time_to_sleep = ft_atoi_philo(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = ft_atoi_philo(argv[5]);
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (argc == 6 && data->must_eat_count <= 0))
	{
		printf("Error: Invalid or out-of-bound arguments.\n");
		return (1);
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	idx;

	if (!data)
		return ;
	if (data->forks)
	{
		idx = -1;
		while (++idx < data->forks_init)
			pthread_mutex_destroy(&data->forks[idx]);
		free(data->forks);
		data->forks = NULL;
	}
	if (data->print_mutex_init)
		pthread_mutex_destroy(&data->print_mutex);
	if (data->death_mutex_init)
		pthread_mutex_destroy(&data->death_mutex);
	if (data->philos)
	{
		idx = -1;
		while (++idx < data->philos_init)
			pthread_mutex_destroy(&data->philos[idx].meal_mutex);
		free(data->philos);
		data->philos = NULL;
	}
}
