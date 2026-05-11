/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:13:22 by eonen             #+#    #+#             */
/*   Updated: 2026/05/11 14:16:23 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	while (++i < data->num_philos)
	{
		//* açılmazsa önceki threadlerin hepsini geriye doğru kapa öyle çık
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (1);
	}
	//* bu da açılmazsa joinle beklemeye çalış
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (1);
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
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
