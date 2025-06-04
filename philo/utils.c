#include "../philo.h"

long long	get_timestamp_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void	precise_usleep(long ms, t_philo **philo)
{
	long	start;

	(void)philo;
	start = get_timestamp_ms();
	while (get_timestamp_ms() - start < ms)
	{
		if (check_death(philo) == SUCCESS)
			return ;
		usleep(100);
	}
}

int	print_taken_fork(t_philo **philo)
{
	if (check_death(philo) == SUCCESS)
		return (FAILURE);
	pthread_mutex_lock(&(*philo)->data->print_lock);
	printf("%lld  %d has taken a fork\n", get_timestamp_ms()
		- (*philo)->data->start_time, (*philo)->nb);
	pthread_mutex_unlock(&(*philo)->data->print_lock);
	return (SUCCESS);
}
int	print_eat(t_philo **philo)
{
	if (check_death(philo) == SUCCESS)
		return (FAILURE);
	pthread_mutex_lock(&(*philo)->data->print_lock);
	printf("%lld  %d is eating\n", get_timestamp_ms()
		- (*philo)->data->start_time, (*philo)->nb);
	pthread_mutex_unlock(&(*philo)->data->print_lock);
	return (SUCCESS);
}
int	print_sleep(t_philo **philo)
{
	if (check_death(philo) == SUCCESS)
		return (FAILURE);
	pthread_mutex_lock(&(*philo)->data->print_lock);
	printf("%lld  %d is sleeping\n", get_timestamp_ms()
		- (*philo)->data->start_time, (*philo)->nb);
	pthread_mutex_unlock(&(*philo)->data->print_lock);
	return (SUCCESS);
}
int	print_think(t_philo **philo)
{
	if (check_death(philo) == SUCCESS)
		return (FAILURE);
	pthread_mutex_lock(&(*philo)->data->print_lock);
	printf("%lld  %d is thinking\n", get_timestamp_ms()
		- (*philo)->data->start_time, (*philo)->nb);
	pthread_mutex_unlock(&(*philo)->data->print_lock);
	return (SUCCESS);
}
void	print_died(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->data->print_lock);
	printf("%lld  %d died\n", get_timestamp_ms() - (*philo)->data->start_time,
		(*philo)->nb);
	pthread_mutex_unlock(&(*philo)->data->print_lock);
}
