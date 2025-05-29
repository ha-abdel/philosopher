
#include "../philo.h"

void	handle_even_thread(t_philo **philo)
{
	while (1)
	{
		pthread_mutex_lock((*philo)->left);
	// precise_usleep(100);
		pthread_mutex_lock((*philo)->right);
		printf("%lld  %d has taken a fork\n", get_timestamp_ms() - (*philo)->data->start_time, (*philo)->number);
		if((*philo)->must_eat <= 0)
			return;
		eat(philo);
		(*philo)->must_eat--;

		pthread_mutex_unlock((*philo)->left);
		pthread_mutex_unlock((*philo)->right);
		ft_sleep(philo);
		think(philo);
	}
	
}
void	handle_odd_thread(t_philo **philo)
{
	while (1)
	{
		pthread_mutex_lock((*philo)->right);
	// precise_usleep(100);
		pthread_mutex_lock((*philo)->left);
		printf("%lld  %d has taken a fork\n", get_timestamp_ms() - (*philo)->data->start_time, (*philo)->number);
		if((*philo)->must_eat <= 0)
			return;
		eat(philo);
		(*philo)->must_eat--;
		pthread_mutex_unlock((*philo)->right);
		pthread_mutex_unlock((*philo)->left);
		ft_sleep(philo);
		think(philo);
	}
	
}

void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	precise_usleep(100);
	if (philo->number % 2 == 0)
	{
		handle_even_thread(&philo);
	}
	else
	{
		handle_odd_thread(&philo);
	}
	return NULL;
}

int	init_philos(char **av, t_data **data, t_philo ***philos)
{
	int	i;
	t_philo **phil;

	i = 0;
	phil = *philos;
	(*data)->nb_philo = (*data)->args->num_philos;
	while (i < (*data)->nb_philo)
	{
		phil[i] = ft_malloc(sizeof(t_philo), 1);
		if(!(*data)->forks[i])
			(*data)->forks[i] = ft_malloc(sizeof(pthread_mutex_t), 1);
		if(i + 1 < (*data)->nb_philo)
			(*data)->forks[i + 1] = ft_malloc(sizeof(pthread_mutex_t), 1);
		if (!phil[i] || !(*data)->forks[i])
    		return FAILURE;
		pthread_mutex_init(&phil[i]->lock, NULL);
		pthread_mutex_init((*data)->forks[i], NULL);
		phil[i]->data = (*data);
		phil[i]->number = i + 1;
		phil[i]->time_to_die = (*data)->args->time_to_die;
		phil[i]->time_to_eat = (*data)->args->time_to_eat;
		phil[i]->time_to_sleep = (*data)->args->time_to_sleep;
		phil[i]->left = (*data)->forks[i];
		if(i + 1 < (*data)->nb_philo)
			phil[i]->right = (*data)->forks[(i + 1) % (*data)->nb_philo];
		if (av[5])
			phil[i]->must_eat = (*data)->args->must_eat_count;
		i++;
	}
	return (SUCCESS);
}

void	create_thread(t_data **data, t_philo ***philos)
{
	int i =0;
	t_philo **phil;

	phil = *philos;
	while (i < (*data)->nb_philo)
	{
		pthread_create(&phil[i]->thread, NULL, routine, phil[i]);
		i++;
	}
	
	
}

int	parse_args(int ac, char **av, t_data **data, t_philo ***philos)
{
	int	invalid;
	t_philo **phil;

	invalid = 0;
	if (ac != 5 && ac != 6)
		return (printf("invalid args"), FAILURE);
	(*data)->args = ft_malloc(sizeof(t_args), 1);
	if ((*data)->args)
	{
		(*data)->args->num_philos = ft_atoi(av[1], &invalid);
		(*data)->args->time_to_die = ft_atoi(av[2], &invalid);
		(*data)->args->time_to_eat = ft_atoi(av[3], &invalid);
		(*data)->args->time_to_sleep = ft_atoi(av[4], &invalid);
		(*data)->args->must_eat_count = ft_atoi(av[5], &invalid);
	}
    if ((*data)->args->num_philos <= 0 || (*data)->args->time_to_die <= 0 ||
        (*data)->args->time_to_eat <= 0 || (*data)->args->time_to_sleep <= 0 ||
        (ac == 6 && (*data)->args->must_eat_count <= 0))
        	return(printf("args invalid"), FAILURE);
	phil = ft_malloc(sizeof(t_philo *) * ((*data)->args->num_philos), 1);
	(*data)->forks = ft_malloc(sizeof(pthread_mutex_t *)
			* ((*data)->args->num_philos), 1);
	if (!phil || !(*data)->forks || !(*data)->args || invalid)
		return (FAILURE);
	if (init_philos(av, data, &phil))
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
	parse_args(ac, av, &data, &philos);
	create_thread(&data, &philos);
	while (i < data->nb_philo)
	{
		if(pthread_join(philos[i]->thread, NULL) != 0)
			return FAILURE;
		i++;
	}
	return SUCCESS;
	
}