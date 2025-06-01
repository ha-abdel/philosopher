#include "../philo.h"

void	eat(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->lock);
	(*philo)->last_meal = get_timestamp_ms();
	pthread_mutex_unlock(&(*philo)->lock);
	printf("%lld  %d is eating\n", get_timestamp_ms()
		- (*philo)->data->start_time, (*philo)->number);
	precise_usleep((*philo)->time_to_eat, philo);
}

void	ft_sleep(t_philo **philo)
{
    // pthread_mutex_lock(&(*philo)->lock);
    // if (check_death(philo) == SUCCESS)
    // {
    //     pthread_mutex_unlock(&(*philo)->lock);
    //     return;
    // }
    // pthread_mutex_unlock(&(*philo)->lock);
	printf("%lld  %d is sleeping\n", get_timestamp_ms()
		- (*philo)->data->start_time, (*philo)->number);
	precise_usleep((*philo)->time_to_sleep, philo);
}
void	think(t_philo **philo)
{
    pthread_mutex_lock(&(*philo)->lock);
    if (check_death(philo) == SUCCESS)
    {
        pthread_mutex_unlock(&(*philo)->lock);
        return;
    }
    pthread_mutex_unlock(&(*philo)->lock);
	printf("%lld  %d is thinking\n", get_timestamp_ms()
		- (*philo)->data->start_time, (*philo)->number);
	usleep(500);
}

void	*monitoring(void *ptr)
{
	t_philo **phil;
	t_data *data;
	int i;

	phil = (ptr);
	data = phil[0]->data;
	// while (!data->allready)
	// 	usleep(100);
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&phil[i]->lock);
			if (get_timestamp_ms() - phil[i]->last_meal >= phil[i]->time_to_die)
			{
				phil[i]->died = 1;
				phil[i]->data->detect_death = 1;
				printf("%lld  %d died\n", get_timestamp_ms()
					- phil[i]->data->start_time, phil[i]->number);
				pthread_mutex_unlock(&phil[i]->lock);
				return (NULL);
			}
			pthread_mutex_unlock(&phil[i]->lock);
			i++;
		}
	}
	return (NULL);
}