/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eonen <eonen@student.42istanbul.com.tr     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 20:13:58 by eonen             #+#    #+#             */
/*   Updated: 2026/05/09 20:14:00 by eonen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return ((int)(res * sign));
}

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_sim_status(t_data *sim)
{
	int	stat;

	pthread_mutex_lock(&sim->death_mutex);
	stat = sim->someone_died || sim->all_ate_enough; 
	pthread_mutex_unlock(&sim->death_mutex);
	return (stat);
}

void	precise_sleep(long long duration_ms, t_data *sim)
{
	long long	start;

	start = current_time_ms();
	while ((current_time_ms() - start) < duration_ms)
	{
		if (check_sim_status(sim))
			break ;
		usleep(500);
	}
}

void	write_status(t_philo *philo, const char *msg)
{
	long long	time_now;

	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_sim_status(philo->data))
	{
		time_now = current_time_ms() - philo->data->start_time;
		printf("%lld %d %s\n", time_now, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->print_mutex);
}