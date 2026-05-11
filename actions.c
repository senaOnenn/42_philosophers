/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:13:05 by eonen             #+#    #+#             */
/*   Updated: 2026/05/11 14:24:17 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		write_status(philo, "has taken a fork");
		//* öldü mü öldüyse çatalı bırak
		pthread_mutex_lock(philo->right_fork);
		write_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		write_status(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		write_status(philo, "has taken a fork");
	}
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	write_status(philo, "is eating");
	precise_sleep(philo->data->time_to_eat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	write_status(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	long long	delay;

	write_status(philo, "is thinking");
	if (philo->data->num_philos % 2 != 0)
	{
		delay = (philo->data->time_to_eat * 2)
			- philo->data->time_to_sleep;
		if (delay > 0)
			precise_sleep(delay / 2, philo->data);
	}
}
