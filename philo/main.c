/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:13:22 by eonen             #+#    #+#             */
/*   Updated: 2026/06/20 09:48:53 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_stop_flag(t_data *sim)
{
	pthread_mutex_lock(&sim->death_mutex);
	sim->someone_died = 1;
	pthread_mutex_unlock(&sim->death_mutex);
}

static void	handle_thread_error(t_data *data, int limit)
{
	int	j;

	set_stop_flag(data);
	j = -1;
	while (++j < limit)
		pthread_join(data->philos[j].thread, NULL);
}

static void	join_all_threads(t_data *data, pthread_t monitor)
{
	int	i;

	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
}

int	start_threads(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
		{
			handle_thread_error(data, i);
			return (1);
		}
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
	{
		handle_thread_error(data, data->num_philos);
		return (1);
	}
	join_all_threads(data, monitor);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (parse_args(argc, argv, &data))
		return (1);
	if (init_data(&data))
	{
		printf("Error: Initialization failed.\n");
		cleanup(&data);
		return (1);
	}
	if (start_threads(&data))
	{
		printf("Error: Thread creation failed.\n");
		cleanup(&data);
		return (1);
	}
	cleanup(&data);
	return (0);
}
