#include "../philo.h"

void    eat(t_philo **philo)
{
    printf("%lld  %d is eating\n", get_timestamp_ms() - (*philo)->data->start_time, (*philo)->number);
    precise_usleep((*philo)->time_to_eat);
}
void    ft_sleep(t_philo **philo)
{
    printf("%lld  %d is sleeping\n", get_timestamp_ms() - (*philo)->data->start_time, (*philo)->number);
    precise_usleep((*philo)->time_to_sleep);
}
void    think(t_philo **philo)
{
    printf("%lld  %d is thinking\n", get_timestamp_ms() - (*philo)->data->start_time, (*philo)->number);
    precise_usleep((*philo)->time_to_sleep);
}