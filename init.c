/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:13:14 by eonen             #+#    #+#             */
/*   Updated: 2026/05/11 11:39:17 by eonen            ###   ########.fr       */
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
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->must_eat_count = -1;
	if (argc == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
	{
		printf("Error: All arguments must be positive integers.\n");
		return (1);
	}
	if (argc == 6 && data->must_eat_count <= 0)
	{
		printf("Error: Invalid meals count.\n");
		return (1);
	}
	return (0);
}

static int	init_mutexes(t_data *data)
{
	int	indx;

	indx = -1;
	while (++indx < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[indx], NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (1);
	return (0);
}

int	init_data(t_data *data)
{
	int	indx;

	data->someone_died = 0;
	data->all_ate_enough = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
		return (1);
	if (init_mutexes(data) != 0)
		return (1);
	data->start_time = current_time_ms();
	indx = -1;
	while (++indx < data->num_philos)
	{
		data->philos[indx].id = indx + 1;
		data->philos[indx].meals_eaten = 0;
		data->philos[indx].last_meal_time = data->start_time;
		data->philos[indx].data = data;
		data->philos[indx].right_fork = &data->forks[indx];
		data->philos[indx].left_fork = &data->forks[(indx + 1)
			% data->num_philos];
		if (pthread_mutex_init(&data->philos[indx].meal_mutex, NULL) != 0)
			return (1);
	}
	return (0);
}

void	cleanup(t_data *data)
{
	int	idx;

	idx = -1;
	if (data->forks)
	{
		while (++idx < data->num_philos)
			pthread_mutex_destroy(&data->forks[idx]);
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	if (data->philos)
	{
		idx = -1;
		while (++idx < data->num_philos)
			pthread_mutex_destroy(&data->philos[idx].meal_mutex);
		free(data->philos);
	}
}
