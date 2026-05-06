#include "philo.h"

/*
** take_forks:
** Deadlock'u önlemek için asimetrik çatal alma stratejisi.
** Tekler önce sağ, çiftler önce sol çatalı alır.
*/
static void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		write_status(philo, "has taken a fork");
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

/*
** philo_eat:
** Çatalları alır, yemek yeme zamanını günceller ve belirtilen
** time_to_eat süresi kadar bekler.
*/
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

/*
** philo_sleep:
** Simülasyon bitmemişse time_to_sleep süresi kadar uyur.
*/
void	philo_sleep(t_philo *philo)
{
	write_status(philo, "is sleeping");
	precise_sleep(philo->data->time_to_sleep, philo->data);
}

/*
** philo_think:
** Filozofun düşünme eylemini terminale basar.
*/
void	philo_think(t_philo *philo)
{
	write_status(philo, "is thinking");
}