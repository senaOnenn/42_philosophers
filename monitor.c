/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:13:31 by eonen             #+#    #+#             */
/*   Updated: 2026/05/11 14:26:34 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data)
{
	int			i;
	long long	elapsed;

	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		elapsed = current_time_ms() - data->philos[i].last_meal_time;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
		if (elapsed >= data->time_to_die)
		{
			pthread_mutex_lock(&data->print_mutex);
			pthread_mutex_lock(&data->death_mutex);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death_mutex);
			printf("%lld %d died\n",
				current_time_ms() - data->start_time, data->philos[i].id);
			pthread_mutex_unlock(&data->print_mutex);
			return (1);
		}
	}
	return (0);
}

static int	check_all_ate(t_data *data)
{
	int	i;
	int	done;

	if (data->must_eat_count == -1)
		return (0);
	done = 0;
	i = -1;
	while (++i < data->num_philos)
	{
		pthread_mutex_lock(&data->philos[i].meal_mutex);
		if (data->philos[i].meals_eaten >= data->must_eat_count)
			done++;
		pthread_mutex_unlock(&data->philos[i].meal_mutex);
	}
	if (done == data->num_philos)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->all_ate_enough = 1;
		pthread_mutex_unlock(&data->death_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data))
			return (NULL);
		if (check_all_ate(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
