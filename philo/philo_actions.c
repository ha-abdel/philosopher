#include "../philo.h"

void    eat(t_philo **philo)
{
    printf("%ul philo %d is eating", get_timestamp_ms(), (*philo)->number);
    precise_usleep((*philo)->time_to_eat);
}
void    sleep(t_philo **philo)
{
    printf("%ul philo %d is sleeping", get_timestamp_ms(), (*philo)->number);
    precise_usleep((*philo)->time_to_sleep);
}
void    think(t_philo **philo)
{
    printf("%ul philo %d is thinking", get_timestamp_ms(), (*philo)->number);
    precise_usleep((*philo)->time_to_sleep);
}