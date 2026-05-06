#include "philo.h"

/*
** check_death:
** Her filozofun last_meal_time'ına bakarak time_to_die'ı
** geçip geçmediğini kontrol eder.
** Ölen varsa ölüm mesajını basar, someone_died'ı set eder.
** death_mutex ile korunur.
*/
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

/*
** check_all_ate:
** must_eat_count ayarlanmışsa tüm filozofların yeterince
** yiyip yemediğini kontrol eder.
*/
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

/*
** monitor_routine:
** Ana thread'den ayrı çalışır; her 1ms'de ölüm ve
** yeterli yeme kontrolü yapar.
*/
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