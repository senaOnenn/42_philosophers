/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:13:14 by eonen             #+#    #+#             */
/*   Updated: 2026/06/20 14:43:09 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	indx;

	indx = -1;
	while (++indx < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[indx], NULL) != 0)
			return (1);
		data->forks_init++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	data->print_mutex_init = 1;
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (1);
	data->death_mutex_init = 1;
	return (0);
}

static int	init_philos(t_data *data)
{
	int	indx;

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
		data->philos_init++;
	}
	return (0);
}

static void	reset_flags(t_data *data)
{
	data->someone_died = 0;
	data->all_ate_enough = 0;
	data->forks_init = 0;
	data->philos_init = 0;
	data->print_mutex_init = 0;
	data->death_mutex_init = 0;
}

int	init_data(t_data *data)
{
	reset_flags(data);
	data->forks = ft_calloc(data->num_philos, sizeof(pthread_mutex_t));
	data->philos = ft_calloc(data->num_philos, sizeof(t_philo));
	if (!data->forks || !data->philos)
		return (1);
	if (init_mutexes(data) != 0)
		return (1);
	data->start_time = current_time_ms();
	if (init_philos(data) != 0)
		return (1);
	return (0);
}
