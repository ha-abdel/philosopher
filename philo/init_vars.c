#include "../philo.h"

int	init_args(t_data **data, char **av, int ac, int *invalid)
{
	(*data)->args = ft_malloc(sizeof(t_args), 1);
	if (!(*data)->args)
		return (FAILURE);
	(*data)->args->num_philos = ft_atoi(av[1], invalid);
	(*data)->args->time_to_die = ft_atoi(av[2], invalid);
	(*data)->args->time_to_eat = ft_atoi(av[3], invalid);
	(*data)->args->time_to_sleep = ft_atoi(av[4], invalid);
	if (ac == 6)
		(*data)->args->must_eat_count = ft_atoi(av[5], invalid);
	else
		(*data)->infinite = 1;
	return (SUCCESS);
}

int	init_forks(t_data **data)
{
	int	i;

	i = 0;
	while (i < (*data)->nb_philo)
	{
		(*data)->forks[i] = ft_malloc(sizeof(pthread_mutex_t), 1);
		if (!(*data)->forks[i])
			return (FAILURE);
		pthread_mutex_init((*data)->forks[i++], NULL);
	}
	return (SUCCESS);
}

int	init_data(t_data **data, t_philo **phil, int i, int ac)
{
	(*data)->allready = 0;
	phil[i]->data = (*data);
	phil[i]->last_meal = get_timestamp_ms();
	phil[i]->nb = i + 1;
	phil[i]->time_to_die = (*data)->args->time_to_die;
	phil[i]->time_to_eat = (*data)->args->time_to_eat;
	phil[i]->time_to_sleep = (*data)->args->time_to_sleep;
	if (i % 2 == 0)
	{
		phil[i]->left = (*data)->forks[i];
		phil[i]->right = (*data)->forks[(i + 1) % (*data)->nb_philo];
	}
	else
	{
		phil[i]->left = (*data)->forks[(i + 1) % (*data)->nb_philo];
		phil[i]->right = (*data)->forks[i];
	}
	if (ac == 6)
		phil[i]->must_eat = (*data)->args->must_eat_count;
	return (SUCCESS);
}

int	init_philos(int ac, t_data **data, t_philo ***philos)
{
	int		i;
	t_philo	**phil;

	i = 0;
	phil = *philos;
	(*data)->nb_philo = (*data)->args->num_philos;
	if (init_forks(data) == FAILURE)
		return (FAILURE);
	(*data)->allready = 0;
	while (i < (*data)->nb_philo)
	{
		phil[i] = ft_malloc(sizeof(t_philo), 1);
		if (!phil[i])
			return (FAILURE);
		pthread_mutex_init(&phil[i]->lock, NULL);
		if (init_data(data, phil, i++, ac) == FAILURE)
			return (FAILURE);
	}
	pthread_mutex_init(&(*data)->monitor_lock, NULL);
	pthread_mutex_init(&(*data)->print_lock, NULL);
	pthread_mutex_init(&(*data)->death_lock, NULL);
	pthread_mutex_init(&(*data)->eat_lock, NULL);
	return (SUCCESS);
}

int	create_thread(t_data **data, t_philo ***philos)
{
	int	i;

	i = 0;
	while (i < (*data)->nb_philo)
	{
		if (pthread_create(&(*philos)[i]->thread, NULL, routine,
				(*philos)[i]) != 0)
		{
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
