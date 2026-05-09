/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:13:41 by eonen             #+#    #+#             */
/*   Updated: 2026/05/09 20:13:44 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*single_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	write_status(philo, "has taken a fork");
	precise_sleep(philo->data->time_to_die + 1, philo->data);
	pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

void	*philo_routine(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;
	if (philo->data->num_philos == 1)
		return (single_philo_routine(philo));
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!check_sim_status(philo->data))
	{
		philo_eat(philo);
		if (check_sim_status(philo->data))
			break ;
		philo_sleep(philo);
		if (check_sim_status(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}