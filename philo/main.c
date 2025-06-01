
#include "../philo.h"

int	check_death(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->lock);
	if((*philo)->data->detect_death)
	{
		pthread_mutex_unlock(&(*philo)->lock);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&(*philo)->lock);
	return (FAILURE);
}

int	handle_thread(t_philo **philo)
{
	while (1)
	{
		if(check_death(philo) == SUCCESS)
			return FAILURE;
		pthread_mutex_lock((*philo)->right);
		printf("%lld  %d has taken a fork\n", get_timestamp_ms() - (*philo)->data->start_time, (*philo)->number);
		if((*philo)->right == (*philo)->left)
		{
			pthread_mutex_unlock((*philo)->right);
			printf("philo %d died\n", (*philo)->number);
			return FAILURE;
		}
		pthread_mutex_lock((*philo)->left);
		printf("%lld  %d has taken a fork\n", get_timestamp_ms() - (*philo)->data->start_time, (*philo)->number);
		if((*philo)->must_eat <= 0 && !(*philo)->data->infinite)
		{
			pthread_mutex_unlock((*philo)->left);
			pthread_mutex_unlock((*philo)->right);
			return SUCCESS;
		}
		eat(philo);
		(*philo)->must_eat--;
		pthread_mutex_unlock((*philo)->right);
		pthread_mutex_unlock((*philo)->left);
		ft_sleep(philo);
		think(philo);
	}
	return SUCCESS;
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	// while (philo->data->allready)
	// if(philo->number % 2 == 0)
	// 	sleep(100);
	if (handle_thread(&philo) == FAILURE)
		return NULL;
	return NULL;
}


int	parse_args(int ac, char **av, t_data **data, t_philo ***philos)
{
	int	invalid;
	t_philo **phil;

	invalid = 0;
	if (ac != 5 && ac != 6)
		return (printf("invalid args"), FAILURE);
	if (init_args(data, av, ac , &invalid) == FAILURE)
		return FAILURE;
    if ((*data)->args->num_philos <= 0 || (*data)->args->time_to_die < 60 ||
        (*data)->args->time_to_eat < 60 || (*data)->args->time_to_sleep < 60 ||
        (ac == 6 && (*data)->args->must_eat_count < 0))
        	return(printf("args invalid"), FAILURE);
	phil = ft_malloc(sizeof(t_philo *) * ((*data)->args->num_philos), 1);
	(*data)->forks = ft_malloc(sizeof(pthread_mutex_t *)
			* ((*data)->args->num_philos), 1);
	if (!phil || !(*data)->forks || !(*data)->args || invalid)
		return (FAILURE);
	if (init_philos(ac, data, &phil))
		return (FAILURE);
	*philos = phil;
	return SUCCESS;
}

int	main(int ac, char **av)
{
	t_data *data;
	t_philo **philos;
	int  i;

	i = 0;
	philos = NULL;
	data = ft_malloc(sizeof(t_data), 1);
	if (!data)
		return (FAILURE);
	data->start_time = get_timestamp_ms();
	if (parse_args(ac, av, &data, &philos) == FAILURE)
		return FAILURE;
	if (create_thread(&data, &philos) == FAILURE)
		return (FAILURE);
	if (pthread_create(&data->monitor, NULL, monitoring, philos) != 0)
		return (FAILURE);
	while (i < data->nb_philo)
	{
		if(pthread_join(philos[i]->thread, NULL) != 0)
			return (FAILURE);
		i++;
	}
	return SUCCESS;
}
