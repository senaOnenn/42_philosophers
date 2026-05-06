#include "philo.h"

/*
** start_threads:
** Her filozof için thread oluşturur, ardından monitor thread'ini başlatır.
** Son olarak tüm thread'lerin bitmesini (join) bekler.
** Norminette satır sınırını aşmamak için ana fonksiyondan ayrılmıştır.
*/
static int	start_threads(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
			return (1);
	}
	if (pthread_create(&monitor, NULL, monitor_routine, data) != 0)
		return (1);
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < data->num_philos)
		pthread_join(data->philos[i].thread, NULL);
	return (0);
}

/*
** main:
** 1. Argümanları parse et.
** 2. Veri yapılarını başlat.
** 3. Thread'leri çalıştır ve bekle.
** 4. Belleği temizle ve çık.
*/
int	main(int argc, char **argv)
{
	t_data	data;

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