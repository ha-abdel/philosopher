#include "../philo.h"

int	eat(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->data->eat_lock);
	(*philo)->last_meal = get_timestamp_ms();
	print_eat(philo);
	pthread_mutex_unlock(&(*philo)->data->eat_lock);
	precise_usleep((*philo)->time_to_eat, philo);
	if (check_death(philo) == SUCCESS)
		return FAILURE;
	return (SUCCESS);
}

int	ft_sleep(t_philo **philo)
{
	print_sleep(philo);
	precise_usleep((*philo)->time_to_sleep, philo);
	if (check_death(philo) == SUCCESS)
		return FAILURE;
	return (SUCCESS);
}
int	think(t_philo **philo)
{
	print_think(philo);
	// precise_usleep(400, philo);
	usleep(400);
	if (check_death(philo) == SUCCESS)
		return FAILURE;
	return (SUCCESS);
}

int	check_all_ate_enough(t_philo **philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->eat_lock);
		if (philo[i]->must_eat > 0)
			return (pthread_mutex_unlock(&data->eat_lock), FAILURE);
		pthread_mutex_unlock(&data->eat_lock);
		i++;
	}
	return (SUCCESS);
}

void	monitor_unlock(t_data *data)
{
	pthread_mutex_unlock(&data->eat_lock);
	// pthread_mutex_unlock(&data->monitor_lock);
}

int	check_last_meal(t_philo **phil, t_data *data, int i)
{
    // pthread_mutex_lock(&phil[i]->data->print_lock);
	// printf("last meal is %lld\n", get_timestamp_ms() - phil[i]->last_meal);
    // pthread_mutex_unlock(&phil[i]->data->print_lock);
	if (get_timestamp_ms() - phil[i]->last_meal > phil[i]->time_to_die)
	{
		pthread_mutex_lock(&phil[i]->data->death_lock);
		phil[i]->data->death = 1;
		print_died(&phil[i]);
		pthread_mutex_unlock(&phil[i]->data->death_lock);
		monitor_unlock(data);
		return (FAILURE);
	}
	return (SUCCESS);
}

void	*monitoring(void *ptr)
{
	t_philo	**phil;
	t_data	*data;
	int		i;

	phil = ptr;
	data = phil[0]->data;
	while (1)
	{
		i = 0;
		if(data->nb_philo == 1)
			return NULL;
		while (i < data->nb_philo)
		{
			// pthread_mutex_lock(&data->monitor_lock);
			pthread_mutex_lock(&data->eat_lock);
			if (check_last_meal(phil, data, i) == FAILURE)
				return (monitor_unlock(data), NULL);
			monitor_unlock(data);
			if (check_all_ate_enough(phil, data) == SUCCESS && !data->infinite)
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}
// void	*monitoring(void *ptr)
// {
// 	t_philo	**phil;
// 	t_data	*data;
// 	int		i;

// 	phil = ptr;
// 	data = phil[0]->data;
// 	while (1)
// 	{
// 		i = 0;
// 		while (i < data->nb_philo)
// 		{
// 			pthread_mutex_lock(&data->monitor_lock);
// 			if (check_all_ate_enough(phil, data) == SUCCESS && !data->infinite)
// 				return (pthread_mutex_unlock(&data->monitor_lock), NULL);
// 			pthread_mutex_lock(&data->eat_lock);
// 			if (check_last_meal(phil, data, i) == FAILURE)
// 				return (NULL);
// 			monitor_unlock(data);
// 			i++;
// 		}
// 		usleep(100);
// 	}
// 	return (NULL);
// }
