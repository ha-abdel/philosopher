#include "../philo.h"

long long get_timestamp_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);  // Get current time
    return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

void    precise_usleep(long ms, t_philo **philo)
{
    long start = get_timestamp_ms();
    while (get_timestamp_ms() - start < ms)
    {
        pthread_mutex_lock(&(*philo)->lock);
        if (check_death(philo) == SUCCESS)
        {
            pthread_mutex_unlock(&(*philo)->lock);
            return;
        }
        pthread_mutex_unlock(&(*philo)->lock);
        usleep(100);
    }
}