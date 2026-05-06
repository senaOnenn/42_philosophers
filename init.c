#include "philo.h"

/*
** parse_args:
** Argüman sayısını ve değerlerini kontrol eder.
** (Kendi ft_atoi fonksiyonunu kullanmalısın, atoi YASAKTIR!)
*/
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
	int	idx;

	idx = -1;
	while (++idx < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[idx], NULL) != 0)
			return (1);
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (1);
	return (0);
}

/*
** init_data:
** Çatalları, filozofları ve kontrol mutex'lerini başlatır.
*/
int	init_data(t_data *data)
{
	int	idx;

	data->someone_died = 0;
	data->all_ate_enough = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->forks || !data->philos)
		return (1);
	if (init_mutexes(data) != 0)
		return (1);
	data->start_time = current_time_ms();
	idx = -1;
	while (++idx < data->num_philos)
	{
		data->philos[idx].id = idx + 1;
		data->philos[idx].meals_eaten = 0;
		data->philos[idx].last_meal_time = data->start_time;
		data->philos[idx].data = data;
		data->philos[idx].right_fork = &data->forks[idx];
		data->philos[idx].left_fork = &data->forks[(idx + 1) % data->num_philos];
		if (pthread_mutex_init(&data->philos[idx].meal_mutex, NULL) != 0)
			return (1);
	}
	return (0);
}

/*
** cleanup:
** Tüm mutex'leri ve tahsis edilen bellekleri temizler.
*/
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