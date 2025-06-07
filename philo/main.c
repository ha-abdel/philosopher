
#include "../philo.h"

int	check_death(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->data->death_lock);
	if ((*philo)->data->death)
	{
		pthread_mutex_unlock(&(*philo)->data->death_lock);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&(*philo)->data->death_lock);
	return (FAILURE);
}

void	handle_thread_unlock(t_philo **philo)
{
	// pthread_mutex_unlock(&(*philo)->data->eat_lock);
	pthread_mutex_unlock((*philo)->left);
	pthread_mutex_unlock((*philo)->right);
}

int	handle_thread(t_philo **philo)
{
	while (1)
	{
		if (check_death(philo) == SUCCESS)
			return (FAILURE);
		pthread_mutex_lock((*philo)->right);
		print_taken_fork(philo);
		if ((*philo)->right == (*philo)->left)
		{
			return (pthread_mutex_unlock((*philo)->right), print_died(philo),
				FAILURE);
		}
		pthread_mutex_lock((*philo)->left);
		print_taken_fork(philo);
		pthread_mutex_lock(&(*philo)->data->eat_lock);
		if ((*philo)->must_eat <= 0 && !(*philo)->data->infinite)
			return (pthread_mutex_unlock(&(*philo)->data->eat_lock),
				handle_thread_unlock(philo), SUCCESS);
		pthread_mutex_unlock(&(*philo)->data->eat_lock);
		if (eat(philo) == FAILURE)
			return (handle_thread_unlock(philo), FAILURE);
		pthread_mutex_lock(&(*philo)->data->eat_lock);
		(*philo)->must_eat--;
		pthread_mutex_unlock(&(*philo)->data->eat_lock);
		handle_thread_unlock(philo);
		if (ft_sleep(philo) == FAILURE || think(philo) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	if (philo->nb % 2 == 0)
		usleep(100);
	handle_thread(&philo);
	return (NULL);
}

int	parse_args(int ac, char **av, t_data **data, t_philo ***philos)
{
	int		invalid;
	t_philo	**phil;

	invalid = 0;
	if (ac != 5 && ac != 6)
		return (printf("invalid args"), FAILURE);
	if (init_args(data, av, ac, &invalid) == FAILURE)
		return (FAILURE);
	if ((*data)->args->num_philos <= 0 || (*data)->args->time_to_die < 60
		|| (*data)->args->time_to_eat < 60 || (*data)->args->time_to_sleep < 60
		|| (ac == 6 && (*data)->args->must_eat_count < 0))
		return (printf("args invalid"), FAILURE);
	phil = ft_malloc(sizeof(t_philo *) * ((*data)->args->num_philos), 1);
	(*data)->forks = ft_malloc(sizeof(pthread_mutex_t *)
			* ((*data)->args->num_philos), 1);
	if (!phil || !(*data)->forks || !(*data)->args || invalid)
		return (FAILURE);
	if (init_philos(ac, data, &phil))
		return (FAILURE);
	*philos = phil;
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_data	*data;
	t_philo	**philos;
	int		i;

	i = 0;
	philos = NULL;
	data = ft_malloc(sizeof(t_data), 1);
	if (!data)
		return (FAILURE);
	data->start_time = get_timestamp_ms();
	if (parse_args(ac, av, &data, &philos) == FAILURE)
		return (FAILURE);
	if (create_thread(&data, &philos) == FAILURE)
		return (FAILURE);
	if (pthread_create(&data->monitor, NULL, monitoring, philos) != 0)
		return (FAILURE);
	while (i < data->nb_philo)
	{
		if (pthread_join(philos[i]->thread, NULL) != 0)
			return (FAILURE);
		i++;
	}
	pthread_join(data->monitor, NULL);
	ft_malloc(0, 0);
	return (SUCCESS);
}
